/// ---------------------------------------------------------------------------
// This file is part of SimpleCT. The SimpleCT software is in the public domain,
// furnished "as is", without technical support, and with no warranty, express or
// implied, as to its usefulness for any purpose.
//
// measurement.h
// Measurement class header file.
//
// Author: Florian Otte
// ---------------------------------------------------------------------------
#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <wx/event.h>
#include <wx/stopwatch.h>
#include <wx/timer.h>

#include "threads.h"
#include "serial.h"

class PHYWE09058_99;
class Arduino;
class Tomography;

class wxString;

class Measurement : CustomThreadClass {
public:
	Measurement( boost::shared_ptr<Tomography> ptrTomography );

	// Basic control - these are most important
	int Start_Measurement();
	int Stop_Measurement();
	int Pause_Measurement();
	int Resume_Measurement();

	// Manual mode - use for calibration and testing
	// Instead of starting a separate thread (like the measurement one) a simpler
	// approach via wxTimer is implemented
	// Manual mode and measurement mode are mutually exclusive
	void manual_mode_xray_on( bool ON );
	void manual_mode_drive_motors( bool ON, int tpos, int apos );

	// Getters
	double get_measurement_progress();
	int get_measurement_state();
	double get_azimu_motor_position();
	double get_trans_motor_position();
	wxString get_elapsed_time_string();

	// Setters
	void set_detectorrows( bool Increase );
	void set_angles( bool Increase );
	void set_voltage( bool Increase );
	void set_current( bool Increase );

	struct MeasurementProperties {
		int _ExposureTime_millisec;
		int _Start_Point;
		struct sObject {
			int Min_microm;
			int Max_microm;
			int Steps;
		} Object;
		struct sAngle {
			int Min_millideg;
			int Max_millideg;
			int Steps;
		} Angle;
		struct sXrayDevice {
			double Voltage_kV;
			double Current_mA;
		} XrayDevice;
		struct sManualMode {
			int Tpos_setpoint_microm;
			int Apos_setpoint_millideg;
		} ManualMode;
	};
	MeasurementProperties get_properties();
	void set_properties( MeasurementProperties& NewProperties );

	void init_device_xraydev( std::string Port );
	void init_device_xraydev(std::string Port, SerialDevice::TIMING NewTiming );
	void init_device_arduino( std::string Port );
	void init_device_arduino(std::string Port, SerialDevice::TIMING NewTiming );
	void calibrate_arduino();
	void move_trans_motor( double Value );
	void move_azimu_motor( double Value );

	enum enumMeasurementState{
		Idle = 0,
		CaptureIn_Progress = 1,
		CaptureIs_Paused = 2,

		ManualMode_Ard = 3,
		ManualMode_Xray = 4,
		ManualMode_Both = 5
	};

	SerialDevice::TIMING get_arduino_serial_timing();
	SerialDevice::TIMING get_xraydev_serial_timing();
private:
	// Measurement routine, called from the measurement thread
	wxThread::ExitCode Task();
	void OnThread_DestructorCall();

	// These methods are called from secondary thread context and
	// contain the functional core of this class
	wxThread::ExitCode threadfunc_measurement();
	wxThread::ExitCode threadfunc_manual_mode();

	// Private setters
	void set_measurement_progress(  double Progress  );
	void set_measurement_state(  int NewState  );
	void set_azimu_motor_position( double Value );
	void set_trans_motor_position( double Value );

	// Send events to main GUI
	// These are just simple wrappers for wxWidget's AddPendingEvent method to simplify event
	// generation and sending
	// We are using events here because updates might occur at any time and from different
	// thread contexts
	void gui_event_update_tpos( int tpos );
	void gui_event_update_apos( int apos );
	void gui_event_update_counts( int counts );
	void gui_event_update_progress( int progress );
	void gui_event_update_xrayprop( bool HV_on);
	void gui_event_update_clock( );
	void gui_event_device_error( int device_type, wxString what );
	void gui_event_measurement_end( int errors_during_measurement );

	// Hardware pointers
	boost::shared_ptr<PHYWE09058_99> _pXraytube;
	boost::shared_ptr<Arduino> _pArduino;

	// Pointer, used whenever new readings are to be registered
	boost::shared_ptr<Tomography> _pTomography;

	// Properties
	MeasurementProperties _MyProperties;
	wxCriticalSection _MyPropertiesCS;
	double _progress_measurement;
	wxCriticalSection _progress_measurementCS;

	enumMeasurementState _State;
	wxCriticalSection _StateCS;

	double _azimu_motor_position;
	double _trans_motor_position;
	wxCriticalSection _MotorPosCS;

	wxStopWatch _sw;
};
const int MEASUREMENT_STARTED_ID = 		200000;
const int MEASUREMENT_ENDED_ID = 		200001;
const int MEASUREMENT_ERROR_ID = 		200002;
const int MEASUREMENT_UPDATED_ID = 		200003;
const int DEVICE_ERROR = 				300000;

const int TPOS_UPDATED = 				400000;
const int APOS_UPDATED = 				400001;
const int COUNTS_UPDATED = 				400003;
const int PROGRESS_UPDATED = 			400004;
const int CLOCK_UPDATED = 				400005;
const int XRAY_PROP_UPDATED =			400006;

DECLARE_EVENT_TYPE(MEASUREMENT_STARTED_ID,  wxCommandEvent)
DECLARE_EVENT_TYPE(MEASUREMENT_ENDED_ID,  wxCommandEvent)
DECLARE_EVENT_TYPE(MEASUREMENT_ERROR_ID,  wxCommandEvent)
DECLARE_EVENT_TYPE(MEASUREMENT_UPDATED_ID,  wxCommandEvent)
DECLARE_EVENT_TYPE(DEVICE_ERROR,  wxCommandEvent)
DECLARE_EVENT_TYPE( TPOS_UPDATED, wxCommandEvent )
DECLARE_EVENT_TYPE( APOS_UPDATED, wxCommandEvent )
DECLARE_EVENT_TYPE( COUNTS_UPDATED, wxCommandEvent )
DECLARE_EVENT_TYPE( PROGRESS_UPDATED, wxCommandEvent )
DECLARE_EVENT_TYPE( CLOCK_UPDATED, wxCommandEvent )
DECLARE_EVENT_TYPE( XRAY_PROP_UPDATED, wxCommandEvent )


#endif /* MEASUREMENT_H_ */
