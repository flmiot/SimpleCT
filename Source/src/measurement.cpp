#define MAX_ERRORS_PER_RUN 20

#include "measurement.h"

#include <stdexcept>

#include "device_arduino.h"
#include "device_phywe09058_99.h"
#include "tomography.h"
#include "wx_frames.h"

#include "wx/msgdlg.h"


Measurement::Measurement( boost::shared_ptr<Tomography> ptrTomography )
: _pXraytube( new PHYWE09058_99() ), _pArduino( new Arduino() ),
  _pTomography( ptrTomography ),
  _progress_measurement( 0 ), _State(Idle), _azimu_motor_position( 0 ),
  _trans_motor_position( 0 ), _sw(), CustomThreadClass()
  {
	_MyProperties._ExposureTime_millisec = 1000;
	_MyProperties._Start_Point = 0;
	_MyProperties.Object.Min_microm = -25000;
	_MyProperties.Object.Max_microm = 25000;
	_MyProperties.Angle.Min_millideg = 0;
	_MyProperties.Angle.Max_millideg = 180000;
	_MyProperties.Object.Steps = 64;
	_MyProperties.Angle.Steps = 64;
	_MyProperties.XrayDevice.Voltage_kV = 0.0;
	_MyProperties.XrayDevice.Current_mA = 0.0;
	_MyProperties.ManualMode.Tpos_setpoint_microm = 0;
	_MyProperties.ManualMode.Apos_setpoint_millideg = 0;

	_sw.Pause();
}

int Measurement::Start_Measurement() {
	if(this->get_measurement_state() != Idle) return 1;
	this->set_measurement_state( Measurement::CaptureIn_Progress );
	this->StartTask();
	_sw.Start();
	return 0;
}

int Measurement::Stop_Measurement() {
	_sw.Pause();
	return this->StopTask();
}

int Measurement::Pause_Measurement() {
	_sw.Pause();
	this->set_measurement_state( Measurement::CaptureIs_Paused );
	return 0;
}

int Measurement::Resume_Measurement() {
	_sw.Resume();
	this->set_measurement_state( Measurement::CaptureIn_Progress );
	return 0;
}

// Manual mode implementation
void Measurement::manual_mode_xray_on(bool ON) {
	// Turn ON manual mode
	if( ON ){
		if( this->get_measurement_state() == Idle ){
			this->set_measurement_state( ManualMode_Xray );
			this->StartTask();
		}
		if( this->get_measurement_state() == ManualMode_Ard )
			this->set_measurement_state( ManualMode_Both );
		else return;
	}
	// Turn OFF manual mode
	if( !ON ){
		if( this->get_measurement_state() == ManualMode_Xray )
			this->set_measurement_state( Idle );
		if( this->get_measurement_state() == ManualMode_Both )
			this->set_measurement_state( ManualMode_Ard );
		else return;
	}
}
void Measurement::manual_mode_drive_motors( bool ON, int tpos, int apos ){
	// Turn ON manual mode
	if( ON ){

		MeasurementProperties prop = get_properties();
		prop.ManualMode.Tpos_setpoint_microm = tpos;
		prop.ManualMode.Apos_setpoint_millideg = apos;
		set_properties( prop );

		if( this->get_measurement_state() == Idle ){
			this->set_measurement_state( ManualMode_Ard );
			this->StartTask();
		}
		if( this->get_measurement_state() == ManualMode_Xray )
			this->set_measurement_state( ManualMode_Both );
		else return;
	}
	// Turn OFF manual mode
	if( !ON ){
		if( this->get_measurement_state() == ManualMode_Ard )
			this->set_measurement_state( Idle );
		if( this->get_measurement_state() == ManualMode_Both )
			this->set_measurement_state( ManualMode_Xray );
		else return;
	}
}

wxThread::ExitCode Measurement::Task() {
	if( this->get_measurement_state() == CaptureIn_Progress )
		return threadfunc_measurement();

	if ( this->get_measurement_state() == ManualMode_Ard
			|| this->get_measurement_state() == ManualMode_Xray
			|| this->get_measurement_state() == ManualMode_Both )
		return threadfunc_manual_mode();

	// All other states are invalid, something is wrong, exit
	return (wxThread::ExitCode) 1;
}

wxThread::ExitCode Measurement::threadfunc_measurement(){
	int iError = 				EXIT_SUCCESS;
	int errors_during_meas = 	0;
	int detectorposition = 		0;
	int angle = 				0;
	int steps_passed = 			0;
	int last_counts = 			0;
	Measurement::MeasurementProperties prop = this->get_properties();
	double step_size_trans = 1.0*( prop.Object.Max_microm - prop.Object.Min_microm) / (prop.Object.Steps -1);
	double step_size_azimu = 1.0*( prop.Angle.Max_millideg - prop.Angle.Min_millideg) / (prop.Angle.Steps -1);
	int pos_trans_micrometers = prop.Object.Min_microm;
	int pos_azimu_millidegree = prop.Angle.Min_millideg;

	while(!_pWorkerThread->TestDestroy()){

		if (this->get_measurement_state() == CaptureIs_Paused) {
			try {
				_pXraytube->TurnOff();
				gui_event_update_xrayprop( false );
			}
			catch( std::runtime_error &err ){
				gui_event_device_error( 1, err.what() ); // 1 Xraydev
				errors_during_meas++;
			}
			// wait for xraytube
			wxThread::Sleep(1000);
		}

		else if (this->get_measurement_state() == CaptureIn_Progress) {

			// Object positioning
			pos_trans_micrometers = prop.Object.Min_microm
					+ detectorposition * step_size_trans;
			pos_azimu_millidegree = prop.Angle.Min_millideg
					+ angle * step_size_azimu;

			if (prop._Start_Point <= steps_passed) {
				// Check if xraytube is ON,
				// turn device on if OFF
				try {
					if (_pXraytube->get(xrayd::HVStatus) == 0) {
						_pXraytube->TurnOn(prop.XrayDevice.Voltage_kV, prop.XrayDevice.Current_mA);
						gui_event_update_xrayprop( true );
						// Wait for x-ray-tube to settle
						wxThread::Sleep(1500);
					}
					gui_event_update_xrayprop( true );
				} catch (std::runtime_error &err) {
					gui_event_device_error( 1, err.what() ); // 1 Xraydev
					errors_during_meas++;
				}

				// Drive the stepper motors
				try {
					_pArduino->set_tpos_micrometer( pos_trans_micrometers );
					gui_event_update_tpos( pos_trans_micrometers );

					//this->set_trans_motor_position(
					//pos_trans_micrometers / 1000.0); delete if a ok

					_pArduino->set_apos_millidegree( pos_azimu_millidegree );
					gui_event_update_apos( pos_azimu_millidegree );

					//this->set_azimu_motor_position(
					//pos_azimu_millidegree / 1000.0 );  delete if a ok

					// Wait till final position
					while ( !_pArduino->get_status().compare( "BUSY" ) ) {
						// Check TestDestroy(), so the user can abort if we get
						// stuck here for some reason
						if ( _pWorkerThread->TestDestroy() )
							break;
						wxThread::Sleep( 40 );
					}
				} catch ( std::runtime_error &err ) {
					gui_event_device_error( 0, err.what() ); // 0 Arduino
					errors_during_meas++;
					wxThread::Sleep( 125 );
				}

				// Collect data
				Tomography::Reading NewData;
				NewData.Detectorpixel = detectorposition;
				NewData.Angle = angle;
				NewData.Valid = true;
				try {
					NewData.Value = _pXraytube->get(xrayd::CountRate, prop._ExposureTime_millisec / 1000);
					//NewData.Value = pos_azimu_millidegree;
					_pTomography->register_new_reading( NewData );
					//last_counts = NewData.Value;
					gui_event_update_counts( NewData.Value );
				} catch ( std::runtime_error &err ) {
					gui_event_device_error( 1, err.what() ); // 1 Xraydev
					errors_during_meas++;
				}
			}

			// Push indices
			(detectorposition % 2 == 0) ? angle++ : angle--;
			if (angle < 0) {
				detectorposition++;
				angle = 0;
			} else if (angle > ( prop.Angle.Steps - 1) ) {
				detectorposition++;
				angle = (prop.Angle.Steps - 1);
			}
			// detectorposition runs FROM 0 TO _MyProperties.Object.Steps - 1
			if (detectorposition == prop.Object.Steps){
				gui_event_update_progress( 1000 * 100);
				break;
			}


			// Calculate progress and post it
			this->set_measurement_progress(
					100 * steps_passed
					/ (1.0f * prop.Object.Steps * prop.Angle.Steps));
			gui_event_update_progress( 100000 * steps_passed
					/ (1.0f * prop.Object.Steps * prop.Angle.Steps) );
			steps_passed++;
			gui_event_update_clock();
		}

		// This has to be checked too, otherwise we might send A LOT of events in
		// short time to the event loop
		if (prop._Start_Point <= steps_passed) {
			// Send event to update interface
			wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED,
					MEASUREMENT_UPDATED_ID);
			event.SetInt(last_counts);
			pMainWindow->GetEventHandler()->AddPendingEvent(event);
		}
	}

	this->set_measurement_progress( 0 );
	gui_event_measurement_end( errors_during_meas );
	return (wxThread::ExitCode) iError;
}

wxThread::ExitCode Measurement::threadfunc_manual_mode(){

	int ExitCode = 0;
	while(!_pWorkerThread->TestDestroy()){

		Measurement::MeasurementProperties prop = this->get_properties();

		// Xray manual mode, will NEVER END on its own (except error) -
		// has to be turned off by user
		try{
			if( this->get_measurement_state() == ManualMode_Xray
					|| this->get_measurement_state() == ManualMode_Both) {

				if ( this->_pXraytube->get( xrayd::HVStatus ) == 0 ) {
					gui_event_update_xrayprop( false );
					this->_pXraytube->TurnOn( prop.XrayDevice.Voltage_kV, prop.XrayDevice.Current_mA );
					gui_event_update_xrayprop( true );
				} else {
					gui_event_update_xrayprop( true );
					int counts = this->_pXraytube->get( xrayd::CountRate, 1 );
				}
			}
		}
		catch( std::runtime_error &err){
			gui_event_device_error(1, err.what() );
		}

		// ------ Arduino manual mode, WILL END when set-point motor positions
		// are reached
		try{
			// Get actual positions and set-points
			int tpos_actual = _pArduino->get_tpos_micrometer();
			int apos_actual = _pArduino->get_apos_millidegree();
			int tpos_setp = prop.ManualMode.Tpos_setpoint_microm;
			int apos_setp = prop.ManualMode.Apos_setpoint_millideg;

			this->_pArduino->set_tpos_micrometer( tpos_setp );
			this->_pArduino->set_apos_millidegree( apos_setp );

			if( this->get_measurement_state() == ManualMode_Ard
					|| this->get_measurement_state() == ManualMode_Both) {

				// Check if set-point positions have been reached
				wxLogMessage( wxString::Format( "%i , %i", tpos_actual, tpos_setp) );
				wxLogMessage( wxString::Format( "%i ", _pArduino->get_tpos_au()) );
				//wxLogMessage( wxString::Format("%i , %i", apos_actual, apos_setp));

				if ( _pArduino->get_status().compare( "BUSY" ) ){
					// True, when arduino status is different from "BUSY"

					// Ready, set measurement_state to ManualMode_Xray or Idle
					// i.e. "turn of" manual_mode_ard
					if( this->get_measurement_state() == ManualMode_Both )
						this->set_measurement_state( ManualMode_Xray );
					if( this-> get_measurement_state() == ManualMode_Ard )
						this->set_measurement_state( Idle );
				}
				gui_event_update_tpos( tpos_actual );
				gui_event_update_apos( apos_actual );
			}
			else {

				if ( !_pArduino->get_status().compare( "BUSY" ) ){
					// True, when arduino status is "BUSY"
					// = Arduino is currently moving: we have to stop motors
					this->_pArduino->set_tpos_micrometer( tpos_actual );
					this->_pArduino->set_apos_millidegree( apos_actual );
				}
			}
		}
		catch( std::runtime_error &err ){
			gui_event_device_error(0, err.what() );
		}

		// End thread when all manual modes are inactive
		try{
			if( this->get_measurement_state() == Idle ){
				int tpos_actual = _pArduino->get_tpos_micrometer();
				int apos_actual = _pArduino->get_apos_millidegree();
				gui_event_update_tpos( tpos_actual );
				gui_event_update_apos( apos_actual );
				break;
			}
		}
		catch( std::runtime_error &err){

		}
		wxThread::Sleep( 125 );
	}
	return (wxThread::ExitCode) ExitCode;
}

int Measurement::get_measurement_state() {
	wxCriticalSectionLocker enter(_StateCS);
	return (int) _State;
}

double Measurement::get_measurement_progress() {
	wxCriticalSectionLocker enter(_progress_measurementCS);
	return _progress_measurement;
}

void Measurement::set_measurement_progress(double Progress) {
	wxCriticalSectionLocker enter(_progress_measurementCS);
	_progress_measurement = Progress;
}


double Measurement::get_azimu_motor_position(){
	wxCriticalSectionLocker lock( _MotorPosCS );
	return _azimu_motor_position;
}

double Measurement::get_trans_motor_position(){
	wxCriticalSectionLocker lock( _MotorPosCS );
	return _trans_motor_position;
}

Measurement::MeasurementProperties Measurement::get_properties() {
	wxCriticalSectionLocker event( _MyPropertiesCS );
	return _MyProperties;
}

void Measurement::set_properties( MeasurementProperties& NewProperties ) {
	wxCriticalSectionLocker event( _MyPropertiesCS );
	_MyProperties = NewProperties;
}

void Measurement::OnThread_DestructorCall() {
	try{
		set_measurement_state(Measurement::Idle);
		_pXraytube->TurnOff();
		gui_event_update_xrayprop( false );
	}
	catch( std::runtime_error &err ){
		// TODO
	}
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, MEASUREMENT_UPDATED_ID);
	event.SetInt(0);
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}

void Measurement::init_device_xraydev(std::string Port) {
	try{
		_pXraytube->Init( Port );
	}
	catch( std::runtime_error &err ){
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, DEVICE_ERROR);
		event.SetInt(1);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		throw;
	}
}

void Measurement::init_device_xraydev(std::string Port, SerialDevice::TIMING NewTiming ) {
	try {
		_pXraytube->set_new_timing( NewTiming );
		_pXraytube->Init( Port );
	} catch ( std::runtime_error &err ) {
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, DEVICE_ERROR );
		event.SetInt( 1 );
		pMainWindow->GetEventHandler()->AddPendingEvent( event );
		throw;
	}
}

void Measurement::init_device_arduino(std::string Port) {
	try{
		_pArduino->Init( Port );
	}
	catch( std::runtime_error &err ){
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, DEVICE_ERROR);
		event.SetInt(0);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		throw;
	}
}

void Measurement::init_device_arduino(std::string Port, SerialDevice::TIMING NewTiming ) {
	try{
		_pArduino->set_new_timing( NewTiming );
		_pArduino->Init( Port );
	}
	catch( std::runtime_error &err ){
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, DEVICE_ERROR);
		event.SetInt(0);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		throw;
	}
}

void Measurement::calibrate_arduino(){
	_pArduino->calibrate();
}

void Measurement::move_trans_motor( double Value ){
	_pArduino->set_tpos_micrometer( Value * 1000);
}
void Measurement::move_azimu_motor( double Value ){
	_pArduino->set_apos_millidegree( Value * 1000);
}

SerialDevice::TIMING Measurement::get_arduino_serial_timing(){
	return _pArduino->get_timing();
}
SerialDevice::TIMING Measurement::get_xraydev_serial_timing(){
	return _pXraytube->get_timing();
}

void Measurement::set_measurement_state( int NewState ) {
	wxCriticalSectionLocker enter(_StateCS);
	_State = (enumMeasurementState)NewState;
}

void Measurement::set_azimu_motor_position( double Value ){
	wxCriticalSectionLocker lock( _MotorPosCS );
	_azimu_motor_position = Value;
}

wxString Measurement::get_elapsed_time_string() {
	wxTimeSpan ts(0, 0, 0, _sw.Time());
	return ts.Format("%H:%M:%S");
}

void Measurement::set_trans_motor_position( double Value ){
	wxCriticalSectionLocker lock( _MotorPosCS );
	_trans_motor_position = Value;
}

void Measurement::set_detectorrows(bool Increase) {
// Dedicated setter for Object.Step member.
// Performs error checking

	wxCriticalSectionLocker lock( _MyPropertiesCS );

	if (Increase) {
		if (_MyProperties.Object.Steps < MAX_TOMOGRAPHY_PIXELS) {
			_MyProperties.Object.Steps *= 2;
		}
	} else {
		if (_MyProperties.Object.Steps > MIN_TOMOGRAPHY_PIXELS) {
			_MyProperties.Object.Steps /= 2;
		}
	}
}

void Measurement::set_angles(bool Increase) {
// Dedicated setter for Angle.Step member.
// Performs error checking

	wxCriticalSectionLocker lock( _MyPropertiesCS );

	if (Increase) {
		if (_MyProperties.Angle.Steps < MAX_TOMOGRAPHY_ANGLES) {
			_MyProperties.Angle.Steps *= 2;
		}
	} else {
		if (_MyProperties.Angle.Steps > MIN_TOMOGRAPHY_ANGLES) {
			_MyProperties.Angle.Steps /= 2;
		}
	}
}


void Measurement::set_voltage(bool Increase) {
// Dedicated setter for XrayDev.Voltage member.
// Performs error checking

	wxCriticalSectionLocker lock( _MyPropertiesCS );

	if (Increase) {
		_MyProperties.XrayDevice.Voltage_kV += 0.5;

	} else {
		_MyProperties.XrayDevice.Voltage_kV -= 0.5;
	}

	// Final checks
	if (_MyProperties.XrayDevice.Voltage_kV > 35.0)
		_MyProperties.XrayDevice.Voltage_kV = 35.0;
	if (_MyProperties.XrayDevice.Voltage_kV < 0.0)
		_MyProperties.XrayDevice.Voltage_kV = 0.0;
}

void Measurement::set_current(bool Increase) {
// Dedicated setter for XrayDev.Current member.
// Performs error checking

	wxCriticalSectionLocker lock( _MyPropertiesCS );

	if (Increase) {
		_MyProperties.XrayDevice.Current_mA += 0.05;
	} else {
		_MyProperties.XrayDevice.Current_mA -= 0.05;
	}
	// Final checks
	if (_MyProperties.XrayDevice.Current_mA > 1.0)
		_MyProperties.XrayDevice.Current_mA = 1.0;
	if (_MyProperties.XrayDevice.Current_mA < 0.0)
		_MyProperties.XrayDevice.Current_mA = 0.0;
}

void Measurement::gui_event_update_tpos( int tpos ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, TPOS_UPDATED);
	event.SetInt( tpos );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_update_apos( int apos ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, APOS_UPDATED);
	event.SetInt( apos );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_update_counts( int counts ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, COUNTS_UPDATED);
	event.SetInt( counts );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_update_progress( int progress ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, PROGRESS_UPDATED);
	event.SetInt( progress );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_update_xrayprop( bool HV_on ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, XRAY_PROP_UPDATED );
	int my_int = ( HV_on ) ? 1 : 0 ;
	event.SetInt( my_int );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_update_clock(){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, CLOCK_UPDATED );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_device_error( int device_type, wxString what ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, DEVICE_ERROR);
	event.SetInt( device_type );
	event.SetString( what );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}
void Measurement::gui_event_measurement_end( int errors_during_measurement ){
	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, MEASUREMENT_ENDED_ID );
	event.SetInt( errors_during_measurement );
	pMainWindow->GetEventHandler()->AddPendingEvent(event);
}

