/*
 Copyright 2016 Florian Otte
 

 Filename: wx_mainframe.cpp
 */

const int Build = 170113;

#include "wx_frames.h"

#include <stdexcept>

#include <wx/event.h>
#include <wx/splash.h>

#include "device_phywe09058_99.h"
#include "device_arduino.h"
#include "measurement.h"
#include "tomography.h"

CustomMainFrame* pMainWindow = NULL;
wxLogWindow* pConsoleWindow = NULL;

/////////////////////////////////////////////////////////
//		CustomMainFrame class implementation
/////////////////////////////////////////////////////////

CustomMainFrame::CustomMainFrame(wxWindow* parent, wxWindowID id,
		const wxString& title, boost::shared_ptr<Tomography> ptrTomography,
		boost::shared_ptr<Measurement> ptrMeasurement) :
		_ProgressValueComputation( 0 ), _ProgressValueMeasurement( 0 ), _label_calib_trans(
				0 ), _label_calib_azimu( 0 ), _pMyTomography( ptrTomography ), _pMyMeasurement(
				ptrMeasurement ), MainFrame( parent, id, title ) {

	SetIcon( wxICON( ApplicationIcon ) );

	// Purpose: CustomMainFrame class ctor

	// this has to be here to get the keyevents working
	wxTheApp->Connect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(CustomMainFrame::on_key_down),
			(wxObject*)0, this);

	wxTheApp->Connect(wxID_ANY, wxEVT_KEY_UP,
			wxKeyEventHandler(CustomMainFrame::on_key_up),
			(wxObject*)0, this);

	// Default Image, which is shown on startup
	const int Size = 512 * 512 * 3;
	unsigned char bits[Size] = { 0 };
	wxImage MyImage( 512, 512, bits, true );

	// add image panels to wxframe
	wxBoxSizer* InnerSizer;
	InnerSizer = new wxBoxSizer( wxHORIZONTAL );
	panel_image_sin = new ImagePanel( image_sinogram, MyImage );
	InnerSizer->Add( panel_image_sin, 1, wxEXPAND, 0 );
	image_sinogram->SetSizer( InnerSizer );
	image_sinogram->Layout();
	wxBoxSizer* InnerSizer2;
	InnerSizer2 = new wxBoxSizer( wxHORIZONTAL );
	panel_image_rec = new ImagePanel( image_reconstruction, MyImage );
	InnerSizer2->Add( panel_image_rec, 1, wxEXPAND );
	image_reconstruction->SetSizer( InnerSizer2 );
	image_reconstruction->Layout();


	// Set statusbar start values
	this->staticText_label_statard->SetLabel( "ARD OK" );
	this->staticText_label_statard->GetFont().SetWeight( wxFONTWEIGHT_NORMAL );
	this->staticText_label_statxraydev->SetLabel( "XRAY OK" );
	this->staticText_label_statxraydev->GetFont().SetWeight(
			wxFONTWEIGHT_NORMAL );

	this->Layout();
	this->UpdateInterface();

	//statusBar->SetStatusText(wxT("Arduino - Status: OK"), 2);
	//statusBar->SetStatusText(wxT("Röntgengerät - Status: OK"), 3);
}

CustomMainFrame::~CustomMainFrame() {

}

void CustomMainFrame::UpdateInterface() {
// Purpose: Update all of the GUI elements

	this->UpdateControls();
	this->UpdateMeasurementDisplay();
	this->UpdateLabels();
	this->UpdateDisplays();
	this->UpdateProgressBars();

	this->Refresh();
	this->Update();
}

void CustomMainFrame::UpdateMeasurementDisplay() {
	wxColour MyGrey = wxColour( 240, 240, 240 );
	wxColour MyYellow = wxColour( 254, 248, 211 );

	int mstate = _pMyMeasurement->get_measurement_state();
	if ( mstate == Measurement::Idle ) {

		// Xray
		this->tc_voltage->SetBackgroundColour( MyYellow );
		this->tc_voltage->SetEditable( true );
		this->tc_current->SetBackgroundColour( MyYellow );
		this->tc_current->SetEditable( true );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyYellow );
		this->tc_azimu_pos->SetEditable( true );
		this->tc_trans_pos->SetBackgroundColour( MyYellow );
		this->tc_trans_pos->SetEditable( true );

		// Panels
		m_panel261->Enable( false );
		m_panel2613->Enable( false );
		m_panel2612->Enable( false );

	}
	else if(mstate == Measurement::ManualMode_Xray ) {

		// Xray
		this->tc_voltage->SetBackgroundColour( MyGrey );
		this->tc_voltage->SetEditable( false );
		this->tc_current->SetBackgroundColour( MyGrey );
		this->tc_current->SetEditable( false );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyYellow );
		this->tc_azimu_pos->SetEditable( true );
		this->tc_trans_pos->SetBackgroundColour( MyYellow );
		this->tc_trans_pos->SetEditable( true );

		// Panels
		m_panel261->Enable( false );
		m_panel2613->Enable( false );
		m_panel2612->Enable( true );

	}
	else if(mstate == Measurement::ManualMode_Ard ) {

		// Xray
		this->tc_voltage->SetBackgroundColour( MyYellow );
		this->tc_voltage->SetEditable( true );
		this->tc_current->SetBackgroundColour( MyYellow );
		this->tc_current->SetEditable( true );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyGrey );
		this->tc_azimu_pos->SetEditable( false );
		this->tc_trans_pos->SetBackgroundColour( MyGrey );
		this->tc_trans_pos->SetEditable( false );

		// Panels
		m_panel261->Enable( false );
		m_panel2613->Enable( false );
		m_panel2612->Enable( false );
	}
	else if(mstate == Measurement::ManualMode_Both ) {

		// Xray
		this->tc_voltage->SetBackgroundColour( MyGrey );
		this->tc_voltage->SetEditable( false );
		this->tc_current->SetBackgroundColour( MyGrey );
		this->tc_current->SetEditable( false );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyGrey );
		this->tc_azimu_pos->SetEditable( false );
		this->tc_trans_pos->SetBackgroundColour( MyGrey );
		this->tc_trans_pos->SetEditable( false );

		// Panels
		m_panel261->Enable( false );
		m_panel2613->Enable( false );
		m_panel2612->Enable( true );
	}
	else if(mstate == Measurement::CaptureIn_Progress ){
		// Xray
		this->tc_voltage->SetBackgroundColour( MyGrey );
		this->tc_voltage->SetEditable( false );
		this->tc_current->SetBackgroundColour( MyGrey);
		this->tc_current->SetEditable( false );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyGrey );
		this->tc_azimu_pos->SetEditable( false );
		this->tc_trans_pos->SetBackgroundColour( MyGrey );
		this->tc_trans_pos->SetEditable( false );
		// Panels
		m_panel261->Enable( true );
		m_panel2613->Enable( true );
		m_panel2612->Enable( true );
	}
	else {
		// Xray
		this->tc_voltage->SetBackgroundColour( MyGrey );
		this->tc_voltage->SetEditable( false );
		this->tc_current->SetBackgroundColour( MyGrey );
		this->tc_current->SetEditable( false );

		// Tpos, Apos
		this->tc_azimu_pos->SetBackgroundColour( MyGrey );
		this->tc_azimu_pos->SetEditable( false );
		this->tc_trans_pos->SetBackgroundColour( MyGrey );
		this->tc_trans_pos->SetEditable( false );
		// Panels
		m_panel261->Enable( false );
		m_panel2613->Enable( false );
		m_panel2612->Enable( false );
	}
}

// Purpose: Set interface labels to their correct state
// Return:	void
// Error:	exception safe / no exceptions
void CustomMainFrame::UpdateLabels() {

	// === panel 'Tomographische Berechnungen' ===
	this->UpdateTomographyLabels();

	// === statusbar ===
	wxString StatusText = wxString::Format( "%i x %i @ %.1fs",
			_pMyTomography->get_tomography_size(),
			_pMyTomography->get_tomography_angles(),
			_pMyMeasurement->get_properties()._ExposureTime_millisec / 1000.0 );
	this->staticText_label_tomography->SetLabel( StatusText );
	//this->statusBar->SetStatusText(StatusText, 0);

	switch ( _pMyMeasurement->get_measurement_state() ) {
	case Measurement::Idle:
		SetStatusText( wxT( "Bereit." ), 0 );
		break;
	case Measurement::CaptureIn_Progress:
		SetStatusText( wxT( "Röntgenaufnahme läuft..." ), 0 );
		break;
	case Measurement::CaptureIs_Paused:
		SetStatusText( wxT( "Röntgenaufnahme unterbrochen." ), 0 );
		break;
	default:
		break;
	}
}

// Purpose: Update tomography computation labels
// Return:	void
// Error:	exception safe / no exceptions
void CustomMainFrame::UpdateTomographyLabels() {
	switch ( _pMyTomography->get_current_computation() ) {
	case Tomography::none: {
		wxString Label;
		Label = (_pMyTomography->is_any_computed( Tomography::Type_Sinogram )) ?
				"Berechnet" : "Nicht berechnet";
		this->staticText_status_fwp->SetLabel( Label );
		Label =
				(_pMyTomography->is_any_computed( Tomography::Type_Slice_fbp )) ?
						"Berechnet" : "Nicht berechnet";
		this->staticText_status_fbp->SetLabel( Label );
		Label = (_pMyTomography->is_any_computed( Tomography::Type_Slice_bp )) ?
				"Berechnet" : "Nicht berechnet";
		this->staticText_status_bp->SetLabel( Label );
		Label =
				(_pMyTomography->is_any_computed( Tomography::Type_Slice_iart )) ?
						"Berechnet" : "Nicht berechnet";
		this->staticText_status_iart->SetLabel( Label );
		break;
	}
	case Tomography::fwp: {
		wxString Progress;
		Progress = wxString::Format( "Fortschritt: %.1f %%",
				_pMyTomography->get_current_computation_progress() );
		this->staticText_status_fwp->SetLabel( Progress );
		break;
	}
	case Tomography::fbp: {
		wxString Progress;
		Progress = wxString::Format( "Fortschritt: %.1f %%",
				_pMyTomography->get_current_computation_progress() );
		this->staticText_status_fbp->SetLabel( Progress );
		break;
	}
	case Tomography::bp: {
		wxString Progress;
		Progress = wxString::Format( "Fortschritt: %.1f %%",
				_pMyTomography->get_current_computation_progress() );
		this->staticText_status_bp->SetLabel( Progress );
		break;
	}
	case Tomography::iart: {
		wxString Progress;
		Progress = wxString::Format( "Fortschritt: %.1f %%",
				_pMyTomography->get_current_computation_progress() );
		this->staticText_status_iart->SetLabel( Progress );
		break;
	}
	}
}

// Purpose: Update buttons & other controls
// Return:	void
// Error:	exception safe / no exceptions
void CustomMainFrame::UpdateControls() {
// Purpose: Enable/disable controls, manage correct button labels

	switch ( _pMyMeasurement->get_measurement_state() ) {

	case Measurement::Idle:
		// Enable/disable
		this->button_shot->Enable( true );
		this->button_stop->Enable( false );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, true );
		this->menuEdit->Enable( ID_MENUITEM_PROPERTIES, true );
		this->m_checkBox1->Enable( true );

		// Labels
		this->button_shot->SetLabel( "Neue Messung" );

		this->button_drive_motor->SetLabel( "Motor fahren" );
		this->button_drive_motor->SetBackgroundColour( wxNullColour );
		this->button_drive_motor->Enable( true );
		this->button_man_xray->SetLabel( "XRAY on" );
		this->button_man_xray->SetBackgroundColour( wxNullColour );
		this->button_man_xray->Enable( true );

		// Min, Max buttons
		this->button_set_min_trans->Enable( true );
		this->button_set_max_trans->Enable( true );
		this->button_set_min_azimu->Enable( true );
		this->button_set_max_azimu->Enable( true );
		break;

	case Measurement::CaptureIn_Progress:
		// Enable/disable
		this->button_stop->Enable( true );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		this->menuEdit->Enable( ID_MENUITEM_PROPERTIES, false );
		this->m_checkBox1->SetValue( false );
		this->m_checkBox1->Enable( false );


		// Labels
		this->button_shot->SetLabel( "Unterbrechen" );

		this->button_drive_motor->SetLabel( "Motor fahren" );
		this->button_drive_motor->SetBackgroundColour( wxNullColour );
		this->button_drive_motor->Enable( false );
		this->button_man_xray->SetLabel( "XRAY on" );
		this->button_man_xray->SetBackgroundColour( wxNullColour );
		this->button_man_xray->Enable( false );


		// Min, Max buttons
		this->button_set_min_trans->Enable( false );
		this->button_set_max_trans->Enable( false );
		this->button_set_min_azimu->Enable( false );
		this->button_set_max_azimu->Enable( false );
		break;

	case Measurement::CaptureIs_Paused:
		// Enable/disable
		this->button_stop->Enable( true );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		this->menuEdit->Enable( ID_MENUITEM_PROPERTIES, false );

		// Labels
		this->button_shot->SetLabel( "Fortsetzen" );
		break;

	case Measurement::ManualMode_Xray:
		this->button_shot->Enable( false );

		this->button_drive_motor->SetLabel( "Motor fahren" );
		this->button_drive_motor->SetBackgroundColour( wxNullColour );
		this->button_man_xray->SetLabel( "XRAY off" );
		this->button_man_xray->SetBackgroundColour(  wxColour( 255, 128, 64 ) );

		// Min, Max buttons
		this->button_set_min_trans->Enable( true );
		this->button_set_max_trans->Enable( true );
		this->button_set_min_azimu->Enable( true );
		this->button_set_max_azimu->Enable( true );
		break;
	case Measurement::ManualMode_Ard:
		this->button_shot->Enable( false );

		this->button_drive_motor->SetLabel( "Motor stop" );
		this->button_drive_motor->SetBackgroundColour(  wxColour( 255, 128, 64 ) );
		this->button_man_xray->SetLabel( "XRAY on" );
		this->button_man_xray->SetBackgroundColour( wxNullColour );

		// Min, Max buttons
		this->button_set_min_trans->Enable( false );
		this->button_set_max_trans->Enable( false );
		this->button_set_min_azimu->Enable( false );
		this->button_set_max_azimu->Enable( false );
		break;
	case Measurement::ManualMode_Both:
		this->button_shot->Enable( false );
		this->button_drive_motor->SetLabel( "Motor stop" );
		this->button_drive_motor->SetBackgroundColour(  wxColour( 255, 128, 64 ) );
		this->button_man_xray->SetLabel( "XRAY off" );
		this->button_man_xray->SetBackgroundColour(  wxColour( 255, 128, 64 ) );

		// Min, Max buttons
		this->button_set_min_trans->Enable( false );
		this->button_set_max_trans->Enable( false );
		this->button_set_min_azimu->Enable( false );
		this->button_set_max_azimu->Enable( false );
		break;
	}

	// === panel 'Tomographische Berechnungen' ===
	switch ( _pMyTomography->get_current_computation() ) {
	case Tomography::none:
		// Labels
		button_fwp->SetLabel( "Berechnen" );
		button_fbp->SetLabel( "Berechnen" );
		button_bp->SetLabel( "Berechnen" );
		button_iart->SetLabel( "Berechnen" );
		// Enable/disable
		button_fbp->Enable( true );
		button_bp->Enable( true );
		button_iart->Enable( false );

		if ( _pMyMeasurement->get_measurement_state() == Measurement::Idle ) {
			button_fwp->Enable( true );
			button_tp_set->Enable( true );
			button_i0_set->Enable( true );
			this->menuFile->Enable( ID_MENUITEM_LOADSINO, true );
		} else {
			button_fwp->Enable( false );
			button_tp_set->Enable( false );
			button_i0_set->Enable( false );
			this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		}
		break;

	case Tomography::fwp:
		// Labels
		button_fwp->SetLabel( "Abbrechen" );
		button_fbp->SetLabel( "Berechnen" );
		button_bp->SetLabel( "Berechnen" );
		button_iart->SetLabel( "Berechnen" );
		// Enable/disable
		button_fwp->Enable( true );
		button_fbp->Enable( false );
		button_bp->Enable( false );
		button_iart->Enable( false );
		button_tp_set->Enable( false );
		button_i0_set->Enable( false );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		break;

	case Tomography::fbp:
		// Labels
		button_fwp->SetLabel( "Berechnen" );
		button_fbp->SetLabel( "Abbrechen" );
		button_bp->SetLabel( "Berechnen" );
		button_iart->SetLabel( "Berechnen" );
		// Enable/disable
		button_fwp->Enable( false );
		button_fbp->Enable( true );
		button_bp->Enable( false );
		button_iart->Enable( false );
		button_tp_set->Enable( false );
		button_i0_set->Enable( false );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		break;

	case Tomography::bp:
		// Labels
		button_fwp->SetLabel( "Berechnen" );
		button_fbp->SetLabel( "Berechnen" );
		button_bp->SetLabel( "Abbrechen" );
		button_iart->SetLabel( "Berechnen" );
		// Enable/disable
		button_fwp->Enable( false );
		button_fbp->Enable( false );
		button_bp->Enable( true );
		button_iart->Enable( false );
		button_tp_set->Enable( false );
		button_i0_set->Enable( false );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		break;

	case Tomography::iart:
		// Labels
		button_fwp->SetLabel( "Berechnen" );
		button_fbp->SetLabel( "Abbrechen" );
		button_bp->SetLabel( "Berechnen" );
		button_iart->SetLabel( "Abbrechen" );
		// Enable/disable
		button_fwp->Enable( false );
		button_fbp->Enable( false );
		button_bp->Enable( false );
		button_iart->Enable( true );
		button_tp_set->Enable( false );
		button_i0_set->Enable( false );
		this->menuFile->Enable( ID_MENUITEM_LOADSINO, false );
		break;

	default:
		break;
	}
}

// Purpose: Update progress bars
// Return:	void
// Error:	exception safe / no exceptions
void CustomMainFrame::UpdateProgressBars() {
	this->_ProgressValueComputation =
			_pMyTomography->get_current_computation_progress();
	this->_ProgressValueMeasurement =
			_pMyMeasurement->get_measurement_progress();

	if ( _ProgressValueMeasurement < 0 )
		_ProgressValueMeasurement = 0;
	else if ( _ProgressValueMeasurement > 100 )
		_ProgressValueMeasurement = 100;

	if ( _ProgressValueComputation < 0 )
		_ProgressValueComputation = 0;
	else if ( _ProgressValueComputation > 100 )
		_ProgressValueComputation = 100;

	this->panel_gauge_comp->SetMinSize(
			wxSize(
					this->GetSize().GetWidth() * this->_ProgressValueComputation
							/ 100.f, 4 ) );
	this->panel_gauge_meas->SetMinSize(
			wxSize(
					this->GetSize().GetWidth() * this->_ProgressValueMeasurement
							/ 100.f, 4 ) );

	this->panel_gauges->Layout();
}

void CustomMainFrame::UpdateDisplays() {
	UpdateLeftDisplay();
	UpdateRightDisplay();
}

// This should not throw exceptions....
void CustomMainFrame::UpdateLeftDisplay() {

	wxImage Temp( this->image_sinogram->GetSize().GetWidth(),
			this->image_sinogram->GetSize().GetWidth() );
	int Selection = this->choice_display_left->GetSelection();
	int MinPixelValue = this->slider_left_bottom->GetValue();
	int MaxPixelValue = this->slider_left_top->GetValue();
	try {
		_pMyTomography->export_any_as_wxImage( Selection, Temp, MinPixelValue,
				MaxPixelValue );
		this->panel_image_sin->UpdateImage( Temp );
	} catch ( std::runtime_error &err ) {
		exception_handler( err, false,
				"Linkes Display konnte nicht geupdatet werden" );
	}
}

void CustomMainFrame::UpdateRightDisplay() {

	wxImage Temp( this->image_reconstruction->GetSize().GetWidth(),
			this->image_reconstruction->GetSize().GetWidth() );
	int Selection = this->choice_display_right->GetSelection();
	int MinPixelValue = this->slider_right_bottom->GetValue();
	int MaxPixelValue = this->slider_right_top->GetValue();
	try {
		_pMyTomography->export_any_as_wxImage( Selection, Temp, MinPixelValue,
				MaxPixelValue );
		this->panel_image_rec->UpdateImage( Temp );
	} catch ( std::runtime_error &err ) {
		exception_handler( err, false,
				"Rechtes Display konnte nicht geupdatet werden" );
	}

}

void CustomMainFrame::OpenPropertiesFrame() {
	int answer;

	CustomPropertyDialog* pPropertiesWindow = new CustomPropertyDialog( this );
	answer = pPropertiesWindow->ShowModal();

	if ( answer == wxID_OK ) {
		try {
			_pMyMeasurement->init_device_arduino( arduino::com_port_arduino );
			IndicateDeviceError( this->staticText_label_statard, 0, "ARD OK" );
		} catch ( std::runtime_error &err ) {
			IndicateDeviceError( this->staticText_label_statard, 1, "ARD ERR" );
		}
		try {
			_pMyMeasurement->init_device_xraydev( xrayd::com_port_xraydev );
			IndicateDeviceError( this->staticText_label_statxraydev, 0,
					"XRAY OK" );
		} catch ( std::runtime_error &err ) {
			IndicateDeviceError( this->staticText_label_statxraydev, 1,
					"XRAY ERR" );
		}
	}
	this->UpdateInterface();
	pPropertiesWindow->Destroy();
}

void CustomMainFrame::IndicateDeviceError(wxStaticText *pmylabel, bool error,
		wxString statustext) {
	pmylabel->SetLabel( statustext );
	if ( error ) {
		wxFont NewFont = pmylabel->GetFont();
		NewFont.SetWeight( wxFONTWEIGHT_BOLD );
		pmylabel->SetFont( NewFont );
		pmylabel->SetForegroundColour( *wxRED);
	} else {
		wxFont NewFont = pmylabel->GetFont();
		NewFont.SetWeight( wxFONTWEIGHT_NORMAL );
		pmylabel->SetFont( NewFont );
		pmylabel->SetForegroundColour( *wxBLACK );
	}
}

wxString CustomMainFrame::GetStatusText(int Field) {
	return this->GetStatusText( Field );
}

// ================= Event Handling ================= //

BEGIN_EVENT_TABLE(CustomMainFrame, wxFrame) EVT_COMMAND( COMPUTATION_SUCCESSFULL_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_computation_completed)
EVT_COMMAND( COMPUTATION_ERROR_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_computation_completed)
EVT_COMMAND( COMPUTATION_UPDATED_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_computation_updated)
EVT_COMMAND( MEASUREMENT_STARTED_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_measurement_started)
EVT_COMMAND( MEASUREMENT_ENDED_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_measurement_completed)
EVT_COMMAND( MEASUREMENT_ENDED_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_measurement_completed)
EVT_COMMAND( TPOS_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_tpos_updated)
EVT_COMMAND( APOS_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_apos_updated)
EVT_COMMAND( COUNTS_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_counts_updated)
EVT_COMMAND( PROGRESS_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_progress_updated)
EVT_COMMAND( CLOCK_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_clock_updated)
EVT_COMMAND( XRAY_PROP_UPDATED, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_xrayprop_updated)
EVT_COMMAND( MEASUREMENT_ERROR_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_measurement_error)
EVT_COMMAND( MEASUREMENT_UPDATED_ID, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnThread_measurement_updated)
EVT_COMMAND( DEVICE_ERROR, wxEVT_COMMAND_TEXT_UPDATED, CustomMainFrame::OnDeviceError)
END_EVENT_TABLE()

// Event Handling: Menu items
void CustomMainFrame::on_menuItem_properties_pressed(wxCommandEvent& event) {
	int answer;
	CustomPropertyDialog* pPropertiesWindow = new CustomPropertyDialog( this );
	answer = pPropertiesWindow->ShowModal();
	pPropertiesWindow->Destroy();
	this->UpdateInterface();
}

void CustomMainFrame::on_menuItem_exportdata_pressed(wxCommandEvent& event) {

	// Create default file name
	wxString date = wxDateTime::Now().FormatISODate();
	Measurement::MeasurementProperties prop =
			this->_pMyMeasurement->get_properties();
	wxString device_info = wxString::Format( "%0.1fkV_%0.2fmA_%0.1fs",
			prop.XrayDevice.Voltage_kV, prop.XrayDevice.Current_mA,
			prop._ExposureTime_millisec / 1000. );
	wxString tomo_info = wxString::Format( "MyObject_%ix%i", prop.Object.Steps,
			prop.Angle.Steps );
	wxString default_file_name = "tomo_" + date + "_" + tomo_info + "_"
			+ device_info;

	wxFileDialog saveFileDialog( this,
			_( "Alle Bildaten als ASCII exportieren" ), "", default_file_name,
			"Textdateien (*.txt)|", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if ( saveFileDialog.ShowModal() == wxID_CANCEL )
		return;

	// create filenames
	wxString fname_counts = wxString(
			saveFileDialog.GetPath() + "_counts.txt" );
	//wxString fname_sino = wxString(saveFileDialog.GetPath() + "_sinogramm.txt");
	//wxString fname_sino_fbp = wxString(saveFileDialog.GetPath() + "_sinogramm_ramp.txt");
	//wxString fname_reco_fbp = wxString(saveFileDialog.GetPath() + "_reco_fbp.txt");
	//wxString fname_reco_bp = wxString(saveFileDialog.GetPath() + "_reco_bp.txt");
	//wxString fname_reco_iart = wxString(saveFileDialog.GetPath() + "_iart.txt");

	_pMyTomography->export_any_as_ascii( Tomography::Type_Counts,
			fname_counts.c_str() );
	//_pMyTomography->export_any_as_ascii( Tomography::Type_Sinogram, fname_sino.c_str());
	//_pMyTomography->export_any_as_ascii( Tomography::Type_Sinogram_ramp, fname_sino_fbp.c_str());
	//_pMyTomography->export_any_as_ascii( Tomography::Type_Slice_fbp, fname_reco_fbp.c_str());
	//_pMyTomography->export_any_as_ascii( Tomography::Type_Slice_bp, fname_reco_bp.c_str());
	//_pMyTomography->export_any_as_ascii( Tomography::Type_Slice_iart, fname_reco_iart.c_str());

	// TODO Log
}

void CustomMainFrame::on_menuItem_about_pressed(wxCommandEvent& event) {
	wxBitmap bitmap;
	if ( bitmap.LoadFile( "splash.png", wxBITMAP_TYPE_PNG ) ) {
		wxSplashScreen* splash = new wxSplashScreen( bitmap,
		wxSPLASH_CENTRE_ON_SCREEN, -1, NULL, -1, wxDefaultPosition,
				wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP );
	}
}

void CustomMainFrame::on_menuItem_exit_pressed(wxCommandEvent& event) {

	this->Close( true );
}
void CustomMainFrame::on_menuItem_savesino_pressed(wxCommandEvent& event) {

	int Selection = this->choice_display_left->GetSelection();
	int State = _pMyTomography->get_any_image_state( Selection );
	if ( !(State == Tomography::NoChanges || State == Tomography::Updated) )
		return;

	int Size = _pMyTomography->get_tomography_size();
	int Angles = _pMyTomography->get_tomography_angles();
	wxImage ToSave( Angles, Size );

	int MinPixelValue = this->slider_left_bottom->GetValue();
	int MaxPixelValue = this->slider_left_top->GetValue();

	try {
		_pMyTomography->export_any_as_wxImage( Selection, ToSave, MinPixelValue,
				MaxPixelValue );
	} catch ( std::runtime_error &err ) {
		exception_handler( err, true, "Bildinhalt des linken Displays "
				"konnte nicht gespeichert werden" );
		return;
	}

	wxFileDialog saveFileDialog( this, _( "Sinogramm als Bitmap speichern" ),
			"", "Sinogramm.bmp", "Bitmap Dateien (*.bmp)|*.bmp",
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if ( saveFileDialog.ShowModal() == wxID_CANCEL )
		return;

	ToSave.SaveFile( saveFileDialog.GetPath(), wxBITMAP_TYPE_BMP );
}
void CustomMainFrame::on_menuItem_savereco_pressed(wxCommandEvent& event) {

	int Selection = this->choice_display_right->GetSelection();
	int State = _pMyTomography->get_any_image_state( Selection );
	if ( !(State == Tomography::NoChanges || State == Tomography::Updated) )
		return;

	int Size = _pMyTomography->get_tomography_size();
	wxImage ToSave( Size, Size );

	int MinPixelValue = this->slider_right_bottom->GetValue();
	int MaxPixelValue = this->slider_right_top->GetValue();

	try {
		_pMyTomography->export_any_as_wxImage( Selection, ToSave, MinPixelValue,
				MaxPixelValue );
	} catch ( std::runtime_error &err ) {
		exception_handler( err, true, "Bildinhalt des rechten Displays "
				"konnte nicht gespeichert werden" );
		return;
	}

	wxFileDialog saveFileDialog( this,
			_( "Rekonstruktion als Bitmap speichern" ), "",
			"Rekonstruktion.bmp", "Bitmap Dateien (*.bmp)|*.bmp",
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if ( saveFileDialog.ShowModal() == wxID_CANCEL )
		return;

	ToSave.SaveFile( saveFileDialog.GetPath(), wxBITMAP_TYPE_BMP );
}

void CustomMainFrame::on_menuItem_loadsino_pressed(wxCommandEvent& event) {
	try {
		if ( _pMyMeasurement->get_measurement_state() != Measurement::Idle )
			return;
		if ( _pMyTomography->get_current_computation() != Tomography::none )
			return;

		int answer;
		answer = wxMessageBox(
				"Achtung, alle ungespeicherten Änderungen gehen verloren! "
						"Soll ein Sinogramm geladen werden?",
				"Sinogramm laden?",
				wxYES_NO | wxICON_WARNING, this );

		if ( answer != wxYES )
			return;

		wxFileDialog* OpenDialog = new wxFileDialog( this,
				_( "Sinogramm-Datei wählen" ), wxEmptyString, wxEmptyString,
				_( "Textdatei (*.txt)|" ), wxFD_OPEN, wxDefaultPosition );

		if ( OpenDialog->ShowModal() != wxID_OK ) {
			OpenDialog->Destroy();
			return;
		}

		wxString InputImageName = OpenDialog->GetPath();
		OpenDialog->Destroy();
		_pMyTomography->load_sinogram_from_ascii_file( InputImageName.c_str() );
		this->UpdateLabels();
		this->choice_display_left->SetSelection( Tomography::Type_Sinogram );
		this->UpdateInterface();

		// Log console message
		wxString Message( "Sinogramm-Datei erfolgreich geladen" );
		wxLogMessage( Message );
	} catch ( std::runtime_error& err ) {
		exception_handler( err, false );
	}
}

//  Event Handling: Buttons
void CustomMainFrame::on_button_shot_pressed(wxCommandEvent& event) {
	try {
		int answer;
		switch ( _pMyMeasurement->get_measurement_state() ) {

		case Measurement::Idle: {

			// Transfer entered xray voltage and current values from main interface
			Measurement::MeasurementProperties prop =
					_pMyMeasurement->get_properties();
			double voltage;
			double current;
			this->tc_voltage->GetLabel().ToDouble( &voltage );
			this->tc_current->GetLabel().ToDouble( &current );

			prop.XrayDevice.Voltage_kV = voltage;
			prop.XrayDevice.Current_mA = current;
			_pMyMeasurement->set_properties( prop );

			CustomMeasurementWizard* Measwiz = new CustomMeasurementWizard(
					this );
			answer = Measwiz->RunWizard();
			if ( answer == true ) {

				// The following is one of three ways the tomography is reset
				// 		1. By loading a new sinogram and creating a new tomography on-the-fly
				// 		2. Creating a new tomography from forward-projection
				//	-->	3. Creating a new tomography for measurement

				int size = _pMyMeasurement->get_properties().Object.Steps;
				int angles = _pMyMeasurement->get_properties().Angle.Steps;
				_pMyTomography->reset_tomography( size, angles );

				// Log console message
				wxString Message(
						wxString::Format( "Tomographie neu erzeugt (%d, %d)" ),
						size, angles );
				wxLogMessage( Message );

			}
			Measwiz->Destroy();

			if ( answer == true ) {
				_pMyMeasurement->Start_Measurement();

				// Log console message
				wxString Message( "### Messung gestartet ###" );
				wxLogMessage( Message );

				this->choice_display_left->SetSelection(
						Tomography::Type_Sinogram );
			}
			break;
		}

		case Measurement::CaptureIn_Progress:
			answer = wxMessageBox(
					"Soll die Röntgenaufnahme unterbrochen werden? ",
					"Röntgenaufnahme unterbrechen?", wxYES_NO | wxICON_WARNING,
					this );
			if ( answer == wxYES ) {
				_pMyMeasurement->Pause_Measurement();
				this->UpdateInterface();

				// Log console message
				wxString Message( "### Messung pausiert ###" );
				wxLogMessage( Message );
			}
			break;

		case Measurement::CaptureIs_Paused:
			answer = wxMessageBox(
					"Soll die Röntgenaufnahme fortgesetzt werden? ",
					"Röntgenaufnahme fortsetzen?", wxYES_NO | wxICON_WARNING,
					this );
			if ( answer == wxYES ) {
				_pMyMeasurement->Resume_Measurement();
				this->UpdateInterface();

				// Log console message
				wxString Message( "### Messung fortgesetzt ###" );
				wxLogMessage( Message );
			}
			break;
		}
	} catch ( std::runtime_error &err ) {
		exception_handler( err, true );
	}
}
void CustomMainFrame::on_button_stop_pressed(wxCommandEvent& event) {
	if ( _pMyMeasurement->get_measurement_state() ) {
		int answer = wxMessageBox(
				"Soll die aktive Röntenaufnahme beendet werden?",
				"Röntgenaufnahme beenden?", wxYES_NO | wxICON_WARNING, this );
		if ( answer == wxYES ) {
			_pMyMeasurement->Stop_Measurement();
			this->UpdateInterface();

			// Log console message
			wxString Message( "### Messung gestoppt ###" );
			wxLogMessage( Message );
		};
	}
}
void CustomMainFrame::on_button_man_xray_pressed(wxCommandEvent& event) {
	int mstate = _pMyMeasurement->get_measurement_state();
	if ( mstate == Measurement::Idle
			|| mstate == Measurement::ManualMode_Ard ) {
		double voltage;
		double current;
		this->tc_voltage->GetLabel().ToDouble( &voltage );
		this->tc_current->GetLabel().ToDouble( &current );
		Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
		prop.XrayDevice.Voltage_kV = voltage;
		prop.XrayDevice.Current_mA = current;
		_pMyMeasurement->set_properties( prop );
		_pMyMeasurement->manual_mode_xray_on( true );
	} else if ( mstate == Measurement::ManualMode_Xray
			|| mstate == Measurement::ManualMode_Both ) {
		_pMyMeasurement->manual_mode_xray_on( false );
	} else
		return;
	this->UpdateInterface();
}
void CustomMainFrame::on_button_drive_motor_pressed(wxCommandEvent& event) {
	int mstate = _pMyMeasurement->get_measurement_state();
	if ( mstate == Measurement::Idle
			|| mstate == Measurement::ManualMode_Xray ) {
		double tpos;
		double apos;
		this->tc_trans_pos->GetLabel().ToDouble( &tpos );
		this->tc_azimu_pos->GetLabel().ToDouble( &apos );
		_pMyMeasurement->manual_mode_drive_motors( true, tpos * 1000, apos * 1000 );
	} else if ( mstate == Measurement::ManualMode_Ard
			|| mstate == Measurement::ManualMode_Both) {
		_pMyMeasurement->manual_mode_drive_motors( false, 0, 0 );
	} else
		return;
	this->UpdateInterface();
}
void CustomMainFrame::on_button_set_min_trans_pressed(wxCommandEvent& event) {
	Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
	double trans_pos;
	this->tc_trans_pos->GetLabel().ToDouble( &trans_pos );
	prop.Object.Min_microm = 1000 * trans_pos;
	_pMyMeasurement->set_properties( prop );
}
void CustomMainFrame::on_button_set_max_trans_pressed(wxCommandEvent& event) {
	Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
	double trans_pos;
	this->tc_trans_pos->GetLabel().ToDouble( &trans_pos );
	prop.Object.Max_microm = 1000 * trans_pos;
	_pMyMeasurement->set_properties( prop );
}
void CustomMainFrame::on_button_set_min_azimu_pressed(wxCommandEvent& event) {
	Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
	double azimu_pos;
	this->tc_azimu_pos->GetLabel().ToDouble( &azimu_pos );
	prop.Angle.Min_millideg = 1000 * azimu_pos;
	_pMyMeasurement->set_properties( prop );
}
void CustomMainFrame::on_button_set_max_azimu_pressed(wxCommandEvent& event) {
	Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
	double azimu_pos;
	this->tc_azimu_pos->GetLabel().ToDouble( &azimu_pos );
	prop.Angle.Max_millideg = 1000 * azimu_pos;
	_pMyMeasurement->set_properties( prop );
}
void CustomMainFrame::on_button_fwp_pressed(wxCommandEvent& event) {

	switch ( _pMyTomography->get_current_computation() ) {
	case Tomography::fwp: {
		_pMyTomography->abort_any_computation();

		// Log console message
		wxString Message( "Berechnung: Vorwärtsprojektion abgebrochen" );
		wxLogMessage( Message );

		break;
	}
	case Tomography::none: {

		this->choice_display_left->SetSelection( Tomography::Type_Sinogram );
		CustomComputationWizard* wiz = new CustomComputationWizard( this );
		int answer = wiz->RunWizard();
		if ( answer == true ) {

			int size = _pMyMeasurement->get_properties().Object.Steps;
			int angles = _pMyMeasurement->get_properties().Angle.Steps;
			_pMyTomography->reset_tomography( size, angles );

			wxFileDialog* OpenDialog = new wxFileDialog( this,
					_( "Datei für die Vorwärtsprojektion wählen" ),
					wxEmptyString, wxEmptyString,
					_( "Bitmap files (*.bmp)|*.bmp" ), wxFD_OPEN,
					wxDefaultPosition );

			if ( OpenDialog->ShowModal() != wxID_OK ) {
				OpenDialog->Destroy();
				return;
			}

			wxImage InputImage( OpenDialog->GetPath() );
			OpenDialog->Destroy();

			_pMyTomography->write_to_image_buffer( InputImage );
			_pMyTomography->compute_fwp_from_image_buffer();

			this->UpdateInterface();

			// Log console message
			wxString Message( "Berechnung: Vorwärtsprojektion gestartet" );
			wxLogMessage( Message );
		}
		wiz->Destroy();
		break;
	}
	default:
		return;
	}
}
void CustomMainFrame::on_button_fbp_pressed(wxCommandEvent& event) {

	switch ( _pMyTomography->get_current_computation() ) {
	case Tomography::fbp: {
		_pMyTomography->abort_any_computation();

		// Log console message
		wxString Message( "Berechnung: Gefilterte Rückprojektion abgebrochen" );
		wxLogMessage( Message );

		break;
	}

	case Tomography::none: {
		this->choice_display_right->SetSelection( Tomography::Type_Slice_fbp );
		_pMyTomography->compute_fbp( Tomography::Ramp );

		// Log console message
		wxString Message( "Berechnung: Gefilterte Rückprojektion gestartet" );
		wxLogMessage( Message );

		break;
	}

	default:
		return;
	}
	this->UpdateInterface();
}
void CustomMainFrame::on_button_bp_pressed(wxCommandEvent& event) {
	switch ( _pMyTomography->get_current_computation() ) {
	case Tomography::bp: {
		_pMyTomography->abort_any_computation();

		// Log console message
		wxString Message( "Berechnung: Rückprojektion abgebrochen" );
		wxLogMessage( Message );

		break;
	}

	case Tomography::none: {
		this->choice_display_right->SetSelection( Tomography::Type_Slice_bp );
		_pMyTomography->compute_bp();

		// Log console message
		wxString Message( "Berechnung: Rückprojektion gestartet" );
		wxLogMessage( Message );

		break;
	}

	default:
		return;
	}
}

void CustomMainFrame::on_button_tp_set_pressed(wxCommandEvent& event) {
	double value;
	this->textC_tp->GetLabel().ToDouble( &value );
	_pMyTomography->set_rotation_axis( value );

	// Log console message
	wxString Message(
			wxString::Format( "Neuer Wert: Drehpunkt = %0.4f", value ) );
	wxLogMessage( Message );
}

void CustomMainFrame::on_button_i0_set_pressed(wxCommandEvent& event) {
	int value = wxAtoi( this->textC_i0->GetValue() );
	_pMyTomography->set_i0( value );

	// Log console message
	wxString Message(
			wxString::Format( "Neuer Wert: Impulsrate Airscan = %d", value ) );
	wxLogMessage( Message );
}

void CustomMainFrame::on_deadpixel_checkbox_clicked(wxCommandEvent& event) {
	_pMyTomography->set_correct_dead_pixels( this->m_checkBox1->IsChecked() );
	this->UpdateInterface();
}

//  Event Handling: Choice
void CustomMainFrame::on_choice_display_left_pressed(wxCommandEvent& event) {
	this->UpdateDisplays();
}
void CustomMainFrame::on_choice_display_right_pressed(wxCommandEvent& event) {
	this->UpdateDisplays();
}

void CustomMainFrame::on_Close(wxCloseEvent& event) {
	int answer;
	if ( _pMyMeasurement->get_measurement_state() ) {
		answer =
				wxMessageBox(
						"Röntgenaufnahme aktiv. Soll das Programm wirklich beendet werden?",
						"Programm beenden?",
						wxYES_NO | wxICON_WARNING, this );
	} else {
		answer = wxMessageBox( "Soll das Programm beendet werden?",
				"Programm beenden?", wxYES_NO, this );
	}
	if ( answer == wxYES ) {
		if ( _pMyMeasurement->get_measurement_state() ) {
			_pMyMeasurement->Stop_Measurement();
		}
		Destroy();
	};
}
void CustomMainFrame::on_mainframe_size_event(wxSizeEvent& event) {
	this->UpdateProgressBars();
	this->UpdateDisplays();
	event.Skip();
}

void CustomMainFrame::on_sash_position_changed(wxSplitterEvent& event) {
	//this->UpdateDisplays();
}

void CustomMainFrame::on_key_down(wxKeyEvent& event) {
	if ( event.GetKeyCode() == WXK_F1 && pConsoleWindow != NULL ) {
		static bool ConsoleWindowStatus = true;
		pConsoleWindow->Show( ConsoleWindowStatus );
		ConsoleWindowStatus = !ConsoleWindowStatus;
	} else
		event.Skip();
}

void CustomMainFrame::on_key_up(wxKeyEvent& event) {
	event.Skip();
}

// Event handling : Threads
void CustomMainFrame::OnThread_computation_completed(wxCommandEvent& evt) {
	try {
		this->UpdateInterface();
		this->UpdateProgressBars();

		// Log console message
		wxString Message( "Berechnung: ... Berechnung abgeschlossen" );
		wxLogMessage( Message );

	} catch ( std::runtime_error &err ) {
		wxMessageBox( err.what() );
	}
}

void CustomMainFrame::OnThread_measurement_started(wxCommandEvent& evt) {
	try {
		this->UpdateInterface();
	} catch ( std::runtime_error &err ) {
		wxMessageBox( err.what() );
	}
}

void CustomMainFrame::OnThread_computation_updated(wxCommandEvent& evt) {
	try {
		this->UpdateTomographyLabels();
		this->UpdateProgressBars();
	} catch ( std::runtime_error &err ) {
		wxMessageBox( err.what() );
	}

}

void CustomMainFrame::OnThread_measurement_completed(wxCommandEvent& evt) {
	try {
		this->UpdateInterface();
	} catch ( std::runtime_error &err ) {
		wxMessageBox( err.what() ); // Soll hier weg, UpdateInterface darf keine Exceptions schmeißen
	}
}

void CustomMainFrame::OnThread_tpos_updated(wxCommandEvent& evt) {
	double tpos = 1 / 1000. * evt.GetInt();
	wxString label_tpos = wxString::Format( "%.2f", tpos );
	this->tc_trans_pos->SetLabel( label_tpos );
	m_panel2614->Layout();
	m_panel2614->Refresh();

}
void CustomMainFrame::OnThread_apos_updated(wxCommandEvent& evt) {
	double apos = 1 / 1000. * evt.GetInt();
	wxString label_apos = wxString::Format( "%.2f", apos );
	this->tc_azimu_pos->SetLabel( label_apos );
	m_panel2615->Layout();
	m_panel2615->Refresh();
}
void CustomMainFrame::OnThread_counts_updated(wxCommandEvent& evt) {
	int counts = evt.GetInt();
	wxString label_counts = wxString::Format( "%i Imp / s", counts );
	this->staticText_label_counts->SetLabel( label_counts );
	m_panel2612->Layout();
	m_panel2612->Refresh();
	this->UpdateInterface();
}
void CustomMainFrame::OnThread_xrayprop_updated( wxCommandEvent& evt ){
	Measurement::MeasurementProperties prop = _pMyMeasurement->get_properties();
	wxString str_voltage = wxString::Format("%.1f", prop.XrayDevice.Voltage_kV);
	wxString str_current = wxString::Format("%.2f", prop.XrayDevice.Current_mA);
	this->tc_voltage->SetLabel( str_voltage );
	this->tc_current->SetLabel( str_current );
	m_panel2611->Layout();
	m_panel2611->Refresh();

	if( evt.GetInt() ){
		this->st_xray_status->SetLabel("ON");
	}
	else {
		this->st_xray_status->SetLabel("OFF");
	}
}
void CustomMainFrame::OnThread_clock_updated( wxCommandEvent& evt ){
	wxString duration = _pMyMeasurement->get_elapsed_time_string();
	this->staticText_label_duration->SetLabel( duration );
}
void CustomMainFrame::OnThread_progress_updated(wxCommandEvent& evt) {
	double progress = 1 / 1000. * evt.GetInt();
	wxString label_progress = wxString::Format( "%.1f %%", progress );
	this->staticText_label_progress->SetLabel( label_progress );
	m_panel2613->Layout();
	m_panel2613->Refresh();
}

void CustomMainFrame::OnThread_measurement_updated(wxCommandEvent& evt) {
	try {
		// Update Measurement display
		this->panel_measurement_display->Enable( true );
		Measurement::MeasurementProperties prop =
				_pMyMeasurement->get_properties();
		int counts = evt.GetInt();
//		this->staticText_label_duration->SetLabel(
//				_pMyMeasurement->get_elapsed_time_string() );

		wxString label_status_xraydev = wxString::Format( "%.1f kV @ %.2f mA",
				prop.XrayDevice.Voltage_kV, prop.XrayDevice.Current_mA );
		wxString label_counts = wxString::Format( "%i Imp / s", counts );
//		wxString label_progress = wxString::Format( "%.1f %%",
//				_pMyMeasurement->get_measurement_progress() );
		wxString label_apos = wxString::Format( "%.2f",
				_pMyMeasurement->get_azimu_motor_position() );
		wxString label_tpos = wxString::Format( "%.2f",
				_pMyMeasurement->get_trans_motor_position() );

//		this->staticText_label_xraydev->SetLabel( label_status_xraydev );
//		this->staticText_label_counts->SetLabel( label_counts );
//		this->staticText_label_progress->SetLabel( label_progress );
//		this->staticText_label_apos->SetLabel( label_apos );
//		this->staticText_label_tpos->SetLabel( label_tpos );

//		this->tc_voltage->SetLabel(
//				wxString::Format( "%.1f", prop.XrayDevice.Voltage_kV ) );
//		this->tc_current->SetLabel(
//				wxString::Format( "%.2f", prop.XrayDevice.Current_mA ) );
//		this->tc_trans_pos->SetLabel( label_tpos );
//		this->tc_azimu_pos->SetLabel( label_apos );

		this->UpdateInterface();

		// Log console message
		wxString Message(
				"# Messung: Impulse = " + label_counts + " | Winkel = "
						+ label_apos + " | Position = " + label_tpos + " ~ ( "
						+ label_status_xraydev + ")" );
		wxLogMessage( Message );

	} catch ( std::runtime_error &err ) {
		wxMessageBox( err.what() );
	}
}

void CustomMainFrame::OnThread_measurement_error(wxCommandEvent& evt) {
	wxMessageBox( "Es sind mehrere kritische Fehler aufgetreten. "
			"Die Messung sollte nicht fortgesetzt werden. "
			"Sind alle Geräte verbunden und einsatzbereit?",
			"Kritischer Fehler",
			wxICON_ERROR );
	try {
		_pMyMeasurement->init_device_arduino( arduino::com_port_arduino );
	} catch ( ... ) {

	}
	try {
		_pMyMeasurement->init_device_xraydev( xrayd::com_port_xraydev );
	} catch ( ... ) {

	}
	this->UpdateInterface();
}

void CustomMainFrame::OnDeviceError(wxCommandEvent& evt) {
	switch ( evt.GetInt() ) {
	case 0: {
		// Arduino
		IndicateDeviceError( this->staticText_label_statard, 1, "ARD ERR" );

		//Log console message
		wxString Message( "### ERROR ARDUINO: " + evt.GetString() );
		wxLogMessage( Message );

		break;
	}

	case 1: {
		// Xraydev
		IndicateDeviceError( this->staticText_label_statxraydev, 1,
				"XRAY ERR" );

		//Log console message
		wxString Message( "### ERROR RÖNTGENRÖHRE: " + evt.GetString() );
		wxLogMessage( Message );

		break;
	}

	default:
		break;
	}
}

/////////////////////////////////////////////////////////
//		CustomConsoleFrame class implementation
/////////////////////////////////////////////////////////
CustomPropertyDialog::CustomPropertyDialog(CustomMainFrame* parent) :
		_parent( parent ), PropertyDialog( parent ) {
	this->textCtrl_comport_arduino->SetLabel( arduino::com_port_arduino );
	this->textCtrl_comport_xraydev->SetLabel( xrayd::com_port_xraydev );

	SerialDevice::TIMING ard_timing = _parent->_pMyMeasurement->get_arduino_serial_timing();
	this->tc_tim_ard_service_restart->SetLabel(
			wxString::Format( "%i", ard_timing.SERVICE_RESTART_DELAY ) );
	this->tc_tim_ard_read_timeout->SetLabel(
			wxString::Format( "%i", ard_timing.TIMEOUT_READ ) );
	this->tc_tim_ard_write_timeout->SetLabel(
			wxString::Format( "%i", ard_timing.TIMEOUT_WRITE ) );
	this->tc_tim_ard_message_delay->SetLabel(
			wxString::Format( "%i", ard_timing.NEXT_MESSAGE_DELAY ) );

	SerialDevice::TIMING xray_timing = _parent->_pMyMeasurement->get_xraydev_serial_timing();
	this->tc_tim_xray_service_restart->SetLabel(
			wxString::Format( "%i", xray_timing.SERVICE_RESTART_DELAY ) );
	this->tc_tim_xray_read_timeout->SetLabel(
			wxString::Format( "%i", xray_timing.TIMEOUT_READ ) );
	this->tc_tim_xray_write_timeout->SetLabel(
			wxString::Format( "%i", xray_timing.TIMEOUT_WRITE ) );
	this->tc_tim_xray_message_delay->SetLabel(
			wxString::Format( "%i", xray_timing.NEXT_MESSAGE_DELAY ) );
}

CustomPropertyDialog::~CustomPropertyDialog() {
	xrayd::com_port_xraydev = std::string(
			this->textCtrl_comport_xraydev->GetValue().mb_str() );
	arduino::com_port_arduino = std::string(
			this->textCtrl_comport_arduino->GetValue().mb_str() );
}

wxString CustomPropertyDialog::get_comtext_xraydev() {
	return this->textCtrl_comport_xraydev->GetValue();
}

wxString CustomPropertyDialog::get_comtext_arduino() {
	return this->textCtrl_comport_arduino->GetValue();
}

void CustomPropertyDialog::on_button_testcom_xraydev_pressed(
		wxCommandEvent& event) {
	xrayd::com_port_xraydev = std::string(
			this->textCtrl_comport_xraydev->GetValue().mb_str() );
	SerialDevice::TIMING NewTiming;
	NewTiming.SERVICE_RESTART_DELAY = wxAtoi( this->tc_tim_xray_service_restart->GetLabel().c_str());
	NewTiming.TIMEOUT_READ = wxAtoi( this->tc_tim_xray_read_timeout->GetLabel().c_str());
	NewTiming.TIMEOUT_WRITE = wxAtoi( this->tc_tim_xray_write_timeout->GetLabel().c_str());
	NewTiming.NEXT_MESSAGE_DELAY = wxAtoi( this->tc_tim_xray_message_delay->GetLabel().c_str());

	try {
		_parent->_pMyMeasurement->init_device_xraydev(arduino::com_port_arduino, NewTiming );
		this->staticText_info_xraydev->SetLabel(
				wxT( "Status: OK, verbunden" ) );
		_parent->IndicateDeviceError(
				this->_parent->staticText_label_statxraydev, 0, "XRAY OK" );
		wxMessageBox( "Das Röntgengerät ist bereit.",
				"Verbindung erfolgreich hergestellt", wxICON_INFORMATION );
	} catch ( std::runtime_error &err ) {
		_parent->exception_handler( err, true );
		this->staticText_info_xraydev->SetLabel(
				wxT( "Status: Keine Verbindung" ) );
		_parent->IndicateDeviceError(
				this->_parent->staticText_label_statxraydev, 1, "XRAY ERR" );
	}
}

void CustomPropertyDialog::on_button_testcom_ardunio_pressed(
		wxCommandEvent& event) {
	arduino::com_port_arduino = std::string(
			this->textCtrl_comport_arduino->GetValue().mb_str() );
	SerialDevice::TIMING NewTiming;
	NewTiming.SERVICE_RESTART_DELAY = wxAtoi( this->tc_tim_ard_service_restart->GetLabel().c_str());
	NewTiming.TIMEOUT_READ = wxAtoi( this->tc_tim_ard_read_timeout->GetLabel().c_str());
	NewTiming.TIMEOUT_WRITE = wxAtoi( this->tc_tim_ard_write_timeout->GetLabel().c_str());
	NewTiming.NEXT_MESSAGE_DELAY = wxAtoi( this->tc_tim_ard_message_delay->GetLabel().c_str());

	try {
		_parent->_pMyMeasurement->init_device_arduino( arduino::com_port_arduino, NewTiming );

		this->staticText_info_arduino->SetLabel(
				wxT( "Status: OK, verbunden" ) );
		_parent->IndicateDeviceError( this->_parent->staticText_label_statard,
				0, "ARD OK" );
		wxMessageBox( "Arduino Leonardo ist bereit.",
				"Verbindung erfolgreich hergestellt", wxICON_INFORMATION );
	} catch ( std::runtime_error &err ) {
		_parent->exception_handler( err, "Arduino Leonardo" );
		this->staticText_info_arduino->SetLabel(
				wxT( "Status: Keine Verbindung" ) );
		_parent->IndicateDeviceError( this->_parent->staticText_label_statard,
				1, "ARD ERR" );
	} catch ( ... ) {

	}
}

void CustomPropertyDialog::on_button_ok_pressed( wxCommandEvent& event){
	arduino::com_port_arduino = std::string(
				this->textCtrl_comport_arduino->GetValue().mb_str() );
	xrayd::com_port_xraydev = std::string(
				this->textCtrl_comport_xraydev->GetValue().mb_str() );
	SerialDevice::TIMING NewTiming;
	NewTiming.SERVICE_RESTART_DELAY = wxAtoi( this->tc_tim_ard_service_restart->GetLabel().c_str());
	NewTiming.TIMEOUT_READ = wxAtoi( this->tc_tim_ard_read_timeout->GetLabel().c_str());
	NewTiming.TIMEOUT_WRITE = wxAtoi( this->tc_tim_ard_write_timeout->GetLabel().c_str());
	NewTiming.NEXT_MESSAGE_DELAY = wxAtoi( this->tc_tim_ard_message_delay->GetLabel().c_str());
	try {
		_parent->_pMyMeasurement->init_device_arduino( arduino::com_port_arduino, NewTiming );

		this->staticText_info_arduino->SetLabel(
				wxT( "Status: OK, verbunden" ) );
		_parent->IndicateDeviceError( this->_parent->staticText_label_statard,
				0, "ARD OK" );
	} catch ( std::runtime_error &err ) {
		_parent->exception_handler( err, "Arduino Leonardo" );
		this->staticText_info_arduino->SetLabel(
				wxT( "Status: Keine Verbindung" ) );
		_parent->IndicateDeviceError( this->_parent->staticText_label_statard,
				1, "ARD ERR" );
	}
	NewTiming.SERVICE_RESTART_DELAY = wxAtoi( this->tc_tim_xray_service_restart->GetLabel().c_str());
	NewTiming.TIMEOUT_READ = wxAtoi( this->tc_tim_xray_read_timeout->GetLabel().c_str());
	NewTiming.TIMEOUT_WRITE = wxAtoi( this->tc_tim_xray_write_timeout->GetLabel().c_str());
	NewTiming.NEXT_MESSAGE_DELAY = wxAtoi( this->tc_tim_xray_message_delay->GetLabel().c_str());

	try {
		_parent->_pMyMeasurement->init_device_xraydev(arduino::com_port_arduino, NewTiming );
		this->staticText_info_xraydev->SetLabel(
				wxT( "Status: OK, verbunden" ) );
		_parent->IndicateDeviceError(
				this->_parent->staticText_label_statxraydev, 0, "XRAY OK" );
	} catch ( std::runtime_error &err ) {
		_parent->exception_handler( err, false );
		this->staticText_info_xraydev->SetLabel(
				wxT( "Status: Keine Verbindung" ) );
		_parent->IndicateDeviceError(
				this->_parent->staticText_label_statxraydev, 1, "XRAY ERR" );
	}
	this->EndModal( wxID_OK );
}

void CustomMainFrame::exception_handler(std::runtime_error &err,
		bool ShowMessageBox) {
	wxString Message( err.what() );
	Message = "Error: " + Message;
	wxLogMessage( Message );
	if ( ShowMessageBox )
		wxMessageBox( err.what(), "Ein Fehler ist aufgetreten.", wxICON_ERROR );
}
void CustomMainFrame::exception_handler(std::runtime_error &err,
		bool ShowMessageBox, wxString AdditionalMessage) {
	wxString Message( err.what() );
	Message = "Error: " + Message + " (" + AdditionalMessage + ")";
	wxLogMessage( Message );
	if ( ShowMessageBox )
		wxMessageBox( err.what(), "Ein Fehler ist aufgetreten.", wxICON_ERROR );
}

void CustomMainFrame::exception_handler(boost::system::system_error &err,
		std::string device_name, bool ShowMessageBox) {
	wxString the_device_name =
			(device_name.length()) ?
					device_name : "unbekanntes serielles Gerät";
	wxString message;

	message = wxString(
			"Es ist ein Geräte- oder Verbindungsfehler für " + the_device_name
					+ " aufgetreten. System Error Code: " );
	message = message + wxString::Format( "%i", err.code().value() );
	wxLogMessage( message );

	if ( ShowMessageBox )
		wxMessageBox( message,
				"Geräte- oder Verbindungsfehler für " + the_device_name,
				wxICON_ERROR );
}

void CustomMainFrame::exception_handler(boost::system::system_error &err,
		bool ShowMessageBox) {
	exception_handler( err, "" );
}

/*
 CustomMeasurementStartDialog::CustomMeasurementStartDialog(
 CustomMainFrame* parent) :  MeasurementStartDialog( parent, wxID_ANY, _T("Neue Messung starten")){

 try{
 parent->_pMyMeasurement->init_device_arduino( arduino::com_port_arduino );
 this->textC_arduino->SetLabel("OK");
 }
 catch(...){
 this->textC_arduino->SetLabel("ERROR");
 this->m_button12->Enable(false);
 }
 try{
 parent->_pMyMeasurement->init_device_xraydev( xrayd::com_port_xraydev );
 this->textC_xraydev->SetLabel("OK");
 }
 catch(...){
 this->textC_xraydev->SetLabel("ERROR");
 this->m_button12->Enable(false);
 }
 double Voltage = parent->_pMyMeasurement->get_properties().XrayDevice.Voltage;
 double Current = parent->_pMyMeasurement->get_properties().XrayDevice.Current;
 this->textC_xrayvol->SetLabel(wxString::Format( "%.1f", Voltage ));
 this->textC_xraycur->SetLabel(wxString::Format( "%.1f", Current ));

 int DetectorRows = parent->_pMyMeasurement->get_properties().Object.Steps;
 int Angles = parent->_pMyMeasurement->get_properties().Angle.Steps;
 this->textC_detector->SetLabel(wxString::Format("%i", DetectorRows));
 this->textC_angles->SetLabel(wxString::Format("%i", Angles));

 int hours = parent->_pMyMeasurement->get_properties().Angle.Steps *
 parent->_pMyMeasurement->get_properties().Object.Steps *
 parent->_pMyMeasurement->get_properties()._ExposureTime_millisec / 3600000;
 int minutes = parent->_pMyMeasurement->get_properties().Angle.Steps *
 parent->_pMyMeasurement->get_properties().Object.Steps *
 parent->_pMyMeasurement->get_properties()._ExposureTime_millisec / 60000 - hours * 60;

 this->textC_duration->SetLabel(wxString::Format("%ih %im", hours, minutes));
 }
 */

CustomMeasurementWizard::CustomMeasurementWizard(CustomMainFrame* parent) :
		_parent( parent ), MeasurementWizard( parent ) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();

	this->staticText_label_detectorrows->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
	this->staticText_label_angles->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
	this->textCtrl_trans_min->SetLabel(
			wxString::Format( "%i", prop.Object.Min_microm / 1000 ) );
	this->textCtrl_trans_max->SetLabel(
			wxString::Format( "%i", prop.Object.Max_microm / 1000 ) );
	this->textCtrl_azim_min->SetLabel(
			wxString::Format( "%i", prop.Angle.Min_millideg / 1000 ) );
	this->textCtrl_azim_max->SetLabel(
			wxString::Format( "%i", prop.Angle.Max_millideg / 1000 ) );

	this->staticText_label_voltage->SetLabel(
			wxString::Format( "%.1f", prop.XrayDevice.Voltage_kV ) );
	this->staticText_label_current->SetLabel(
			wxString::Format( "%.2f", prop.XrayDevice.Current_mA ) );
	this->textCtrl_exposure->SetLabel(
			wxString::Format( "%i", prop._ExposureTime_millisec / 1000 ) );

	this->m_radioBox1->SetSelection( 0 );
	this->m_panel25->Enable( false );
	this->m_panel26->Enable( false );
}
;

bool CustomMeasurementWizard::RunWizard() {
	this->GetPageAreaSizer()->Add( this->m_pages.front() );
	return wxWizard::RunWizard( this->m_pages.front() );
}

void CustomMeasurementWizard::on_spin_detectorrows_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_detectorrows( true ); // increase by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_detectorrows->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
}
void CustomMeasurementWizard::on_spin_detectorrows_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_detectorrows( false ); // decrease by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_detectorrows->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
}
void CustomMeasurementWizard::on_spin_angles_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_angles( true ); // increase by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_angles->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
}
void CustomMeasurementWizard::on_spin_angles_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_angles( false ); // decrease by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_angles->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
}
void CustomMeasurementWizard::on_textCtrl_trans_min_changed(
		wxCommandEvent& event) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	prop.Object.Min_microm = 1000
			* wxAtoi( this->textCtrl_trans_min->GetLabel() );
	_parent->_pMyMeasurement->set_properties( prop );
}
void CustomMeasurementWizard::on_textCtrl_trans_max_changed(
		wxCommandEvent& event) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	prop.Object.Max_microm = 1000
			* wxAtoi( this->textCtrl_trans_max->GetLabel() );
	_parent->_pMyMeasurement->set_properties( prop );
}
void CustomMeasurementWizard::on_textCtrl_azim_min_changed(
		wxCommandEvent& event) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	prop.Angle.Min_millideg = 1000
			* wxAtoi( this->textCtrl_azim_min->GetLabel() );
	_parent->_pMyMeasurement->set_properties( prop );
}
void CustomMeasurementWizard::on_textCtrl_azim_max_changed(
		wxCommandEvent& event) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	prop.Angle.Max_millideg = 1000
			* wxAtoi( this->textCtrl_azim_max->GetLabel() );
	_parent->_pMyMeasurement->set_properties( prop );
}
void CustomMeasurementWizard::on_spin_voltage_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_voltage( true );
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_voltage->SetLabel(
			wxString::Format( "%.1f", prop.XrayDevice.Voltage_kV ) );
}
void CustomMeasurementWizard::on_spin_voltage_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_voltage( false );
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_voltage->SetLabel(
			wxString::Format( "%.1f", prop.XrayDevice.Voltage_kV ) );
}
void CustomMeasurementWizard::on_spin_current_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_current( true );
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_current->SetLabel(
			wxString::Format( "%.2f", prop.XrayDevice.Current_mA ) );
}
void CustomMeasurementWizard::on_spin_current_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_current( false );
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_current->SetLabel(
			wxString::Format( "%.2f", prop.XrayDevice.Current_mA ) );
}
void CustomMeasurementWizard::on_textCtrl_exposure_changed(
		wxCommandEvent& event) {
	double NewExposureTime;
	NewExposureTime = wxAtof( this->textCtrl_exposure->GetValue() );
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	prop._ExposureTime_millisec = 1000 * NewExposureTime;
	_parent->_pMyMeasurement->set_properties( prop );
}

void CustomMeasurementWizard::on_m_radioBox1_clicked(wxCommandEvent &event) {
	switch ( this->m_radioBox1->GetSelection() ) {
	case 0:
		this->m_panel25->Enable( false );
		this->m_panel26->Enable( false );
		break;
	case 1:
		this->m_panel25->Enable( true );
		this->m_panel26->Enable( false );
		break;
	case 2:
		this->m_panel25->Enable( true );
		this->m_panel26->Enable( true );
		break;
	}
}

void CustomMainFrame::on_slider_left_top_scroll(wxScrollEvent& event) {
	this->UpdateLeftDisplay();
}

void CustomMainFrame::on_slider_left_bottom_scroll(wxScrollEvent& event) {
	this->UpdateLeftDisplay();
}

void CustomMainFrame::on_slider_right_top_scroll(wxScrollEvent& event) {
	this->UpdateRightDisplay();
}

void CustomMainFrame::on_slider_right_bottom_scroll(wxScrollEvent& event) {
	this->UpdateRightDisplay();
}

CustomComputationWizard::CustomComputationWizard(CustomMainFrame* parent) :
		_parent( parent ), ComputationWizard( parent ) {
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();

	this->staticText_label_detectorrows1->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
	this->staticText_label_angles1->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
}

bool CustomComputationWizard::RunWizard() {
	this->GetPageAreaSizer()->Add( this->m_pages.front() );
	return wxWizard::RunWizard( this->m_pages.front() );
}

void CustomComputationWizard::on_spin_detectorrows_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_detectorrows( true ); // increase by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_detectorrows1->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
}
void CustomComputationWizard::on_spin_detectorrows_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_detectorrows( false ); // decrease by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_detectorrows1->SetLabel(
			wxString::Format( "%i", prop.Object.Steps ) );
}
void CustomComputationWizard::on_spin_angles_up(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_angles( true ); // increase by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_angles1->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
}
void CustomComputationWizard::on_spin_angles_down(wxSpinEvent& event) {
	_parent->_pMyMeasurement->set_angles( false ); // decrease by factor 2 if valid
	Measurement::MeasurementProperties prop =
			_parent->_pMyMeasurement->get_properties();
	this->staticText_label_angles1->SetLabel(
			wxString::Format( "%i", prop.Angle.Steps ) );
}
