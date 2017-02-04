///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WX_BASE_H__
#define __WX_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/dialog.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/radiobox.h>
#include <wx/filepicker.h>
#include <wx/wizard.h>
#include <wx/dynarray.h>
WX_DEFINE_ARRAY_PTR( wxWizardPageSimple*, WizardPages );

///////////////////////////////////////////////////////////////////////////

#define ID_MENUITEM_LOADSINO 1000
#define ID_MENUITEM_SAVESINO 1001
#define ID_MENUITEM_SAVERECO 1002
#define ID_MENUITEM_EXPORTDATA 1003
#define ID_MENUITEM_EXIT 1004
#define ID_MENUITEM_PROPERTIES 1005
#define ID_MENUITEM_ABOUT 1006
#define ID_BUTTON_FWP 1007
#define ID_BUTTON_FBP 1008
#define ID_BUTTON_BP 1009
#define ID_BUTTON_SHOT 1010
#define ID_BUTTON_STOP 1011
#define ID_BUTTON_TESTCOM_XRAYDEV 1012
#define ID_BUTTON_TESTCOM_ARDUINO 1013
#define ID_SPIN_DETECTORROWS 1014
#define ID_SPIN_ANGLES 1015
#define ID_TEXT_TRANS_MIN 1016
#define ID_TEXT_TRANS_MAX 1017
#define ID_TEXT_AZIM_MIN 1018
#define ID_TEXT_AZIM_MAX 1019
#define ID_SPIN_VOLTAGE 1020
#define ID_SPIN_CURRENT 1021
#define ID_TEXT_EXPOSURE 1022

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* menuFile;
		wxMenu* m_menu2;
		wxMenu* menuEdit;
		wxPanel* m_panel29;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel121;
		wxPanel* panel_sin;
		wxChoice* choice_display_left;
		wxPanel* image_sinogram;
		wxStaticText* m_staticText69;
		wxSlider* slider_left_top;
		wxSlider* slider_left_bottom;
		wxPanel* panel_rec;
		wxChoice* choice_display_right;
		wxPanel* image_reconstruction;
		wxStaticText* m_staticText691;
		wxSlider* slider_right_top;
		wxSlider* slider_right_bottom;
		wxPanel* m_panel301;
		wxNotebook* m_notebook1;
		wxPanel* panel_measurement_display;
		wxPanel* m_panel261;
		wxStaticText* m_staticText67;
		wxStaticText* staticText_label_duration;
		wxPanel* m_panel2611;
		wxStaticText* m_staticText671;
		wxStaticText* staticText_label_xraydev;
		wxTextCtrl* tc_voltage;
		wxStaticText* m_staticText157;
		wxTextCtrl* tc_current;
		wxStaticText* m_staticText1571;
		wxPanel* m_panel2612;
		wxStaticText* m_staticText672;
		wxStaticText* staticText_label_counts;
		wxPanel* m_panel26151;
		wxStaticText* m_staticText6751;
		wxStaticText* staticText_label_statard
		;
		wxStaticText* staticText_label_statxraydev;
		wxPanel* m_panel2613;
		wxStaticText* m_staticText673;
		wxStaticText* staticText_label_progress;
		wxPanel* m_panel2614;
		wxStaticText* m_staticText674;
		wxButton* button_set_min_trans;
		wxButton* button_set_max_trans;
		wxStaticText* staticText_label_tpos;
		wxTextCtrl* tc_trans_pos;
		wxStaticText* m_staticText162;
		wxPanel* m_panel2615;
		wxStaticText* m_staticText675;
		wxButton* button_set_min_azimu;
		wxButton* button_set_max_azimu;
		wxStaticText* staticText_label_apos;
		wxTextCtrl* tc_azimu_pos;
		wxStaticText* m_staticText1621;
		wxPanel* m_panel26152;
		wxStaticText* m_staticText6752;
		wxStaticText* staticText_label_tomography
		;
		wxPanel* m_panel26;
		wxStaticText* m_staticText2621;
		wxStaticLine* m_staticline311;
		wxButton* button_fwp;
		wxStaticText* m_staticText43;
		wxStaticText* staticText_status_fwp;
		wxStaticText* m_staticText26211;
		wxStaticLine* m_staticline3111;
		wxButton* button_fbp;
		wxStaticText* m_staticText431;
		wxStaticText* staticText_status_fbp;
		wxStaticText* m_staticText262111;
		wxStaticLine* m_staticline31111;
		wxButton* button_bp;
		wxStaticText* m_staticText432;
		wxStaticText* staticText_status_bp;
		wxStaticText* m_staticText26212;
		wxStaticLine* m_staticline3112;
		wxButton* button_iart;
		wxStaticText* m_staticText433;
		wxStaticText* staticText_status_iart;
		wxButton* button_tp_set;
		wxTextCtrl* textC_tp;
		wxStaticText* m_staticText136;
		wxButton* button_i0_set;
		wxTextCtrl* textC_i0;
		wxStaticText* m_staticText1361;
		wxStaticText* m_staticText140;
		wxCheckBox* m_checkBox1;
		wxPanel* m_panel271;
		wxStaticText* m_staticText1482;
		wxStaticText* st_xray_status;
		wxPanel* m_panel27;
		wxStaticText* m_staticText148;
		wxButton* button_man_xray;
		wxButton* button_drive_motor;
		wxPanel* m_panel28;
		wxStaticText* m_staticText1481;
		wxButton* button_shot;
		wxButton* button_stop;
		wxPanel* m_panel18;
		wxPanel* panel_gauges;
		wxPanel* panel_gauge_comp;
		wxPanel* panel_gauge_meas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_Close( wxCloseEvent& event ) { event.Skip(); }
		virtual void on_key_down( wxKeyEvent& event ) { event.Skip(); }
		virtual void on_key_up( wxKeyEvent& event ) { event.Skip(); }
		virtual void on_mainframe_size_event( wxSizeEvent& event ) { event.Skip(); }
		virtual void on_mainframe_size_event( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void on_menuItem_loadsino_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_savesino_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_savereco_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_exportdata_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_exit_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_properties_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menuItem_about_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_sash_position_changed( wxSplitterEvent& event ) { event.Skip(); }
		virtual void on_choice_display_left_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_slider_left_top_scroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void on_slider_left_bottom_scroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void on_choice_display_right_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_slider_right_top_scroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void on_slider_right_bottom_scroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void on_button_set_min_trans_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_set_max_trans_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_set_min_azimu_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_set_max_azimu_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_fwp_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_fbp_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_bp_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_tp_set_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_i0_set_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_deadpixel_checkbox_clicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_man_xray_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_drive_motor_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_shot_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_stop_pressed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SimpleCT"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,700 ), long style = wxDEFAULT_FRAME_STYLE );
		
		~MainFrame();
		
		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 0 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter3OnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog2
///////////////////////////////////////////////////////////////////////////////
class MyDialog2 : public wxDialog 
{
	private:
	
	protected:
		wxGauge* m_gauge1;
	
	public:
		
		MyDialog2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Bitte warten..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 208,94 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~MyDialog2();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PropertyDialog
///////////////////////////////////////////////////////////////////////////////
class PropertyDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook2;
		wxPanel* prop_panel_xraydev;
		wxStaticText* m_staticText47;
		wxStaticText* m_staticText45;
		wxTextCtrl* textCtrl_comport_xraydev;
		wxButton* button_testcom_xraydev;
		wxStaticLine* m_staticline181;
		wxStaticText* m_staticText1472;
		wxStaticText* m_staticText45214;
		wxTextCtrl* tc_tim_xray_service_restart;
		wxStaticText* m_staticText1512;
		wxStaticText* m_staticText452111;
		wxTextCtrl* tc_tim_xray_read_timeout;
		wxStaticText* m_staticText15112;
		wxStaticText* m_staticText452121;
		wxTextCtrl* tc_tim_xray_write_timeout;
		wxStaticText* m_staticText151112;
		wxStaticText* m_staticText452131;
		wxTextCtrl* tc_tim_xray_message_delay;
		wxStaticText* m_staticText1511111;
		wxStaticLine* m_staticline13;
		wxStaticText* staticText_info_xraydev;
		wxPanel* prop_panel_arduino;
		wxStaticText* m_staticText471;
		wxStaticText* m_staticText452;
		wxTextCtrl* textCtrl_comport_arduino;
		wxButton* button_testcom_ardunio;
		wxStaticLine* m_staticline18;
		wxStaticText* m_staticText147;
		wxStaticText* m_staticText4521;
		wxTextCtrl* tc_tim_ard_service_restart;
		wxStaticText* m_staticText151;
		wxStaticText* m_staticText45211;
		wxTextCtrl* tc_tim_ard_read_timeout;
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText45212;
		wxTextCtrl* tc_tim_ard_write_timeout;
		wxStaticText* m_staticText15111;
		wxStaticText* m_staticText45213;
		wxTextCtrl* tc_tim_ard_message_delay;
		wxStaticText* m_staticText151111;
		wxStaticLine* m_staticline12;
		wxStaticText* staticText_info_arduino;
		wxButton* m_button19;
		wxButton* m_button20;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_button_testcom_xraydev_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_testcom_ardunio_pressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_ok_pressed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PropertyDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Einstellungen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~PropertyDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ConsoleFrame
///////////////////////////////////////////////////////////////////////////////
class ConsoleFrame : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel15;
		wxTextCtrl* textCtrl_console;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_consoleframe_closed( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		ConsoleFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Debug-Fenster"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 394,538 ), long style = wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~ConsoleFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MeasurementWizard
///////////////////////////////////////////////////////////////////////////////
class MeasurementWizard : public wxWizard 
{
	private:
	
	protected:
		wxStaticText* m_staticText61111111111;
		wxStaticText* m_staticText611211111;
		wxStaticText* m_staticText6111211111;
		wxStaticText* m_staticText6112;
		wxStaticText* m_staticText61112;
		wxStaticText* m_staticText611111;
		wxStaticLine* m_staticline51;
		wxStaticText* m_staticText623;
		wxSpinButton* spin_detectorrows;
		wxStaticText* staticText_label_detectorrows;
		wxStaticText* m_staticText6212;
		wxSpinButton* spin_angles;
		wxStaticText* staticText_label_angles;
		wxStaticText* m_staticText181122;
		wxTextCtrl* textCtrl_trans_min;
		wxStaticText* m_staticText18111121;
		wxStaticText* m_staticText1811213;
		wxTextCtrl* textCtrl_trans_max;
		wxStaticText* m_staticText181111131;
		wxStaticText* m_staticText18112111;
		wxTextCtrl* textCtrl_azim_min;
		wxStaticText* m_staticText1811111111;
		wxStaticText* m_staticText18112121;
		wxTextCtrl* textCtrl_azim_max;
		wxStaticText* m_staticText1811111211;
		wxStaticBitmap* m_bitmap21;
		wxStaticText* m_staticText61121111;
		wxStaticText* m_staticText6111111111;
		wxStaticText* m_staticText611121111;
		wxStaticText* m_staticText61121;
		wxStaticText* m_staticText611121;
		wxStaticText* m_staticText6111111;
		wxStaticLine* m_staticline511;
		wxStaticText* m_staticText622;
		wxSpinButton* spin_voltage;
		wxStaticText* staticText_label_voltage;
		wxStaticText* m_staticText371;
		wxStaticText* m_staticText6211;
		wxSpinButton* spin_current;
		wxStaticText* staticText_label_current;
		wxStaticText* m_staticText37;
		wxStaticText* m_staticText1811;
		wxTextCtrl* textCtrl_exposure;
		wxStaticText* m_staticText18111;
		wxStaticText* m_staticText6112111;
		wxStaticText* m_staticText61112111;
		wxStaticText* m_staticText611111111;
		wxStaticText* m_staticText611211;
		wxStaticText* m_staticText6111211;
		wxStaticText* m_staticText61111111;
		wxStaticLine* m_staticline5111;
		wxRadioBox* m_radioBox1;
		wxPanel* m_panel25;
		wxStaticText* m_staticText140;
		wxTextCtrl* textC_pointnumber;
		wxButton* button_set_point_number;
		wxPanel* m_panel26;
		wxStaticText* m_staticText141;
		wxFilePickerCtrl* m_filePicker1;
		wxStaticLine* m_staticline14;
		wxStaticText* m_staticText5311;
		wxStaticLine* m_staticline15;
		wxStaticText* m_staticText532;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_spin_detectorrows_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_detectorrows_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_trans_min_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_trans_max_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_azim_min_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_azim_max_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_spin_voltage_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_voltage_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_current_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_current_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_exposure_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_m_radioBox1_clicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_button_set_point_number_pressed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MeasurementWizard( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Neue Messung starten"), const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE );
		WizardPages m_pages;
		~MeasurementWizard();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MeasurementWizard2
///////////////////////////////////////////////////////////////////////////////
class MeasurementWizard2 : public wxWizard 
{
	private:
	
	protected:
		wxStaticText* m_staticText791;
		wxStaticText* m_staticText801;
		wxStaticText* m_staticText811;
		wxStaticLine* m_staticline9;
		wxStaticText* m_staticText623;
		wxSpinButton* spin_detectorrows;
		wxStaticText* staticText_label_detectorrows;
		wxStaticText* staticText_label_detectorrows1;
		wxStaticText* m_staticText6212;
		wxSpinButton* spin_angles;
		wxStaticText* staticText_label_angles;
		wxStaticText* staticText_label_angles1;
		wxStaticText* m_staticText181122;
		wxTextCtrl* textCtrl_trans_min;
		wxStaticText* m_staticText1811112;
		wxStaticText* m_staticText18111121;
		wxStaticText* m_staticText1811213;
		wxTextCtrl* textCtrl_trans_max;
		wxStaticText* m_staticText18111113;
		wxStaticText* m_staticText181111131;
		wxStaticText* m_staticText18112111;
		wxTextCtrl* textCtrl_azim_min;
		wxStaticText* m_staticText181111111;
		wxStaticText* m_staticText1811111111;
		wxStaticText* m_staticText18112121;
		wxTextCtrl* textCtrl_azim_max;
		wxStaticText* m_staticText181111121;
		wxStaticText* m_staticText1811111211;
		wxStaticBitmap* m_bitmap21;
		wxStaticText* m_staticText8011;
		wxStaticText* m_staticText7911;
		wxStaticText* m_staticText8111;
		wxStaticLine* m_staticline91;
		wxStaticText* m_staticText622;
		wxSpinButton* spin_voltage;
		wxStaticText* staticText_label_voltage;
		wxStaticText* m_staticText371;
		wxStaticText* m_staticText6211;
		wxSpinButton* spin_current;
		wxStaticText* staticText_label_current;
		wxStaticText* m_staticText37;
		wxStaticText* m_staticText1811;
		wxTextCtrl* textCtrl_exposure;
		wxStaticText* m_staticText18111;
		wxStaticText* m_staticText181111;
		wxStaticText* m_staticText8012;
		wxStaticText* m_staticText8112;
		wxStaticText* m_staticText7912;
		wxStaticLine* m_staticline92;
		wxStaticText* m_staticText5311;
		wxStaticText* m_staticText532;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_spin_detectorrows_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_detectorrows_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_trans_min_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_trans_max_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_azim_min_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_azim_max_changed( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_spin_voltage_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_voltage_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_current_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_current_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_textCtrl_exposure_changed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MeasurementWizard2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Neue Messung starten"), const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE );
		WizardPages m_pages;
		~MeasurementWizard2();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ComputationWizard
///////////////////////////////////////////////////////////////////////////////
class ComputationWizard : public wxWizard 
{
	private:
	
	protected:
		wxStaticText* m_staticText611111111;
		wxStaticText* m_staticText6112111;
		wxStaticText* m_staticText61112111;
		wxStaticText* m_staticText61122;
		wxStaticLine* m_staticline512;
		wxStaticText* m_staticText103;
		wxStaticText* m_staticText6231;
		wxSpinButton* spin_detectorrows1;
		wxStaticText* staticText_label_detectorrows1;
		wxStaticText* m_staticText62121;
		wxSpinButton* spin_angles1;
		wxStaticText* staticText_label_angles1;
		wxStaticLine* m_staticline16;
		wxStaticText* m_staticText53111;
		wxStaticLine* m_staticline17;
		wxStaticText* m_staticText5321;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_spin_detectorrows_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_detectorrows_up( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_down( wxSpinEvent& event ) { event.Skip(); }
		virtual void on_spin_angles_up( wxSpinEvent& event ) { event.Skip(); }
		
	
	public:
		
		ComputationWizard( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Vorwärtsprojektion starten"), const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE );
		WizardPages m_pages;
		~ComputationWizard();
	
};

#endif //__WX_BASE_H__
