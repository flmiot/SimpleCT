/*
 Copyright 2016 Florian Otte
 
 This file is part of Mneme v0.1 (Mayflower).
 Filename: wx_customframes.h
 */
#ifndef WX_FRAMES_H_
#define WX_FRAMES_H_

#include <boost/shared_ptr.hpp>

#include <wx/wx.h>		// Main wxWidgets header
#include <wx/aboutdlg.h>// wxAboutDialog
#include <wx/msgdlg.h>  // wxMessageBox
#include <wx/filedlg.h> // wxFileDialog

#include "../ext/wx_base.h"	// wxFormBuilder frames

// Forward declarations
class CustomMainFrame;
class CustomConsoleFrame;
class CustomPropertyDialog;
class CustomMeasurementStartDialog;
class CustomMeasurementWizard;
class CustomComputationWizard;

class Tomography;
class Measurement;

class ImagePanel;

namespace boost{
namespace system{
class system_error;
}
}
namespace std{
class runtime_error;
}


extern CustomMainFrame* pMainWindow;
extern wxLogWindow* pConsoleWindow;

// Main interface class
// MainFrame has been build with wxFormBuilder
class CustomMainFrame: public MainFrame {

	friend CustomPropertyDialog;
	friend CustomMeasurementStartDialog;
	friend CustomMeasurementWizard;
	friend CustomComputationWizard;

public:
	CustomMainFrame(
			wxWindow* parent,
			wxWindowID id,
			const wxString& title ,
			boost::shared_ptr<Tomography> ptrTomography,
			boost::shared_ptr<Measurement> ptrMeasurement);
	virtual ~CustomMainFrame();

	void OpenPropertiesFrame();

private:

	// GUI element control
	void UpdateInterface();
	void UpdateMeasurementDisplay();
	void UpdateControls();
	void UpdateLabels();
	void UpdateTomographyLabels();
	void UpdateDisplays();
	void UpdateLeftDisplay();
	void UpdateRightDisplay();
	void UpdateProgressBars();
	void IndicateDeviceError(  wxStaticText *pmylabel, bool error,
			wxString statustext );
	wxString GetStatusText( int Field );

	// Event handling
	void on_Close(wxCloseEvent& event);

	void on_menuItem_about_pressed( wxCommandEvent& event );
	void on_menuItem_exit_pressed( wxCommandEvent& event );
	void on_menuItem_savesino_pressed( wxCommandEvent& event );
	void on_menuItem_savereco_pressed( wxCommandEvent& event );
	void on_menuItem_loadsino_pressed( wxCommandEvent& event );
	void on_menuItem_properties_pressed( wxCommandEvent& event );
	void on_menuItem_exportdata_pressed( wxCommandEvent& event );

	void on_button_shot_pressed( wxCommandEvent& event );
	void on_button_stop_pressed( wxCommandEvent& event );
	void on_button_man_xray_pressed( wxCommandEvent& event );
	void on_button_drive_motor_pressed( wxCommandEvent& event );
	void on_button_set_min_trans_pressed( wxCommandEvent& event );
	void on_button_set_max_trans_pressed( wxCommandEvent& event );
	void on_button_set_min_azimu_pressed( wxCommandEvent& event );
	void on_button_set_max_azimu_pressed( wxCommandEvent& event );

	void on_button_fwp_pressed( wxCommandEvent& event );
	void on_button_fbp_pressed( wxCommandEvent& event );
	void on_button_bp_pressed( wxCommandEvent& event );
	void on_button_tp_set_pressed( wxCommandEvent& event );
	void on_button_i0_set_pressed( wxCommandEvent& event );
	void on_deadpixel_checkbox_clicked( wxCommandEvent& event);

	void on_choice_display_left_pressed( wxCommandEvent& event );
	void on_choice_display_right_pressed( wxCommandEvent& event );

	void on_slider_left_top_scroll( wxScrollEvent& event );
	void on_slider_left_bottom_scroll( wxScrollEvent& event );
	void on_slider_right_top_scroll( wxScrollEvent& event );
	void on_slider_right_bottom_scroll( wxScrollEvent& event );

	void on_key_down( wxKeyEvent& event);
	void on_key_up( wxKeyEvent& event);

	void on_mainframe_size_event(wxSizeEvent &event);
	void on_sash_position_changed( wxSplitterEvent& event );

	void OnThread_computation_completed(wxCommandEvent& evt);
	void OnThread_computation_updated(wxCommandEvent& evt);

	void OnThread_measurement_updated(wxCommandEvent& evt);

	void OnThread_measurement_error(wxCommandEvent& evt);

	void OnThread_measurement_started(wxCommandEvent& evt);
	void OnThread_measurement_completed(wxCommandEvent& evt);
	void OnThread_tpos_updated( wxCommandEvent& evt );
	void OnThread_apos_updated( wxCommandEvent& evt );
	void OnThread_counts_updated( wxCommandEvent& evt );
	void OnThread_xrayprop_updated( wxCommandEvent& evt );
	void OnThread_clock_updated( wxCommandEvent& evt );
	void OnThread_progress_updated( wxCommandEvent& evt );
	void OnDeviceError(wxCommandEvent& evt);


	ImagePanel* panel_image_sin;
	ImagePanel* panel_image_rec;

	// Needed for UpdateProgressBars
	double _ProgressValueComputation;
	double _ProgressValueMeasurement;

	int _label_calib_trans;
	int _label_calib_azimu;

	boost::shared_ptr<Tomography> _pMyTomography;
	boost::shared_ptr<Measurement> _pMyMeasurement;

	// Convenient exception handling
	void exception_handler( std::runtime_error &err, bool ShowMessageBox);
	void exception_handler( std::runtime_error &err, bool ShowMessageBox, wxString AdditionalMessage );
	void exception_handler( boost::system::system_error &err, bool ShowMessageBox);
	void exception_handler( boost::system::system_error &err, std::string device_name, bool ShowMessageBox );
	DECLARE_EVENT_TABLE()

};

class CustomPropertyDialog : public PropertyDialog {
public:
	CustomPropertyDialog(CustomMainFrame* parent);
	~CustomPropertyDialog();

	wxString get_comtext_xraydev();
	wxString get_comtext_arduino();

private:

	CustomMainFrame* _parent;

	// Arduino panel
	void on_button_testcom_ardunio_pressed(wxCommandEvent& event);

	// x-ray-device panel
	void on_button_testcom_xraydev_pressed(wxCommandEvent& event);

	void on_button_ok_pressed( wxCommandEvent& event);


};

class CustomMeasurementWizard : public MeasurementWizard {
public:
	CustomMeasurementWizard(CustomMainFrame* parent);
	bool RunWizard();
	bool RunWizard_fwp 	();

protected:

	// Arduino settings event handlers
	void on_spin_detectorrows_up(wxSpinEvent& event);
	void on_spin_detectorrows_down(wxSpinEvent& event);
	void on_spin_angles_up(wxSpinEvent& event);
	void on_spin_angles_down(wxSpinEvent& event);
	void on_textCtrl_trans_min_changed( wxCommandEvent& event );
	void on_textCtrl_trans_max_changed( wxCommandEvent& event );
	void on_textCtrl_azim_min_changed( wxCommandEvent& event );
	void on_textCtrl_azim_max_changed( wxCommandEvent& event );

	// Tube settings event handlers
	void on_spin_voltage_up(wxSpinEvent& event);
	void on_spin_voltage_down(wxSpinEvent& event);
	void on_spin_current_up(wxSpinEvent& event);
	void on_spin_current_down(wxSpinEvent& event);
	void on_textCtrl_exposure_changed( wxCommandEvent& event );

	void on_m_radioBox1_clicked( wxCommandEvent &event);

	CustomMainFrame* _parent;
};

class CustomComputationWizard : public ComputationWizard {
public:
	CustomComputationWizard(CustomMainFrame* parent);
	bool RunWizard();

protected:

	// Arduino settings event handlers
	void on_spin_detectorrows_up(wxSpinEvent& event);
	void on_spin_detectorrows_down(wxSpinEvent& event);
	void on_spin_angles_up(wxSpinEvent& event);
	void on_spin_angles_down(wxSpinEvent& event);

	CustomMainFrame* _parent;
};



class ImagePanel: public wxPanel {

	friend CustomMainFrame;

	wxImage image;
	wxBitmap resized;
	int w, h;

public:
	ImagePanel(wxPanel* parent,  const wxImage & img) : image(img), wxPanel(parent) {
		w = -1;
		h = -1;

		this->Connect(wxEVT_PAINT, wxPaintEventHandler(ImagePanel::paintEvent) );
		this->Connect(wxEVT_SIZE, wxSizeEventHandler( ImagePanel::OnSize ));
	}

	void UpdateImage(wxImage &Image){
		image = Image;
		this->paintNow(image);
	}

	void paintEvent(wxPaintEvent & evt) {
		wxPaintDC dc(this);
		render(dc);
	}

	void paintNow(wxImage &NewImage) {
			wxClientDC dc(this);
			render(dc, NewImage);
		}

	void OnSize(wxSizeEvent& event) {
		Refresh();
		//skip the event.
		event.Skip();
	}

	void render(wxDC& dc) {
		int neww, newh;
		    dc.GetSize( &neww, &newh );

		    if( neww != w || newh != h )
		    {
		    	int scale;
		    	if(neww < newh) scale = neww;
		    	else scale = newh;

		        resized = wxBitmap( image.Scale( scale, scale /*, wxIMAGE_QUALITY_HIGH*/ ) );
		        w = neww;
		        h = newh;
		        dc.DrawBitmap( resized, 0, 0, false );
		    }else{
		        dc.DrawBitmap( resized, 0, 0, false );
		    }
	}

	void render(wxDC& dc, wxImage &NewImage) {
		int neww, newh;
		dc.GetSize(&neww, &newh);
		resized = wxBitmap(NewImage.Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
		dc.DrawBitmap(resized, 0, 0, false);
	}
};

#endif /* WX_FRAMES_H_ */
