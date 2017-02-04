///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_base.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 380,380 ), wxSize( -1,-1 ) );
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* menuItem_loadsino;
	menuItem_loadsino = new wxMenuItem( menuFile, ID_MENUITEM_LOADSINO, wxString( wxT("Sinogramm laden ") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuItem_loadsino );
	
	m_menu2 = new wxMenu();
	wxMenuItem* m_menu2Item = new wxMenuItem( menuFile, wxID_ANY, wxT("Bilder speichern"), wxEmptyString, wxITEM_NORMAL, m_menu2 );
	wxMenuItem* menuItem_savesino;
	menuItem_savesino = new wxMenuItem( m_menu2, ID_MENUITEM_SAVESINO, wxString( wxT("Linkes Display speichern") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem_savesino );
	
	wxMenuItem* menuItem_savereco;
	menuItem_savereco = new wxMenuItem( m_menu2, ID_MENUITEM_SAVERECO, wxString( wxT("Rechtes Display speichern") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem_savereco );
	
	menuFile->Append( m_menu2Item );
	
	wxMenuItem* menuItem_exportdata;
	menuItem_exportdata = new wxMenuItem( menuFile, ID_MENUITEM_EXPORTDATA, wxString( wxT("Daten exportieren") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuItem_exportdata );
	
	menuFile->AppendSeparator();
	
	wxMenuItem* menuItem_exit;
	menuItem_exit = new wxMenuItem( menuFile, ID_MENUITEM_EXIT, wxString( wxT("Beenden") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuItem_exit );
	
	m_menubar1->Append( menuFile, wxT("Datei") ); 
	
	menuEdit = new wxMenu();
	wxMenuItem* menuItem_properties;
	menuItem_properties = new wxMenuItem( menuEdit, ID_MENUITEM_PROPERTIES, wxString( wxT("Einstellungen") ) , wxEmptyString, wxITEM_NORMAL );
	menuEdit->Append( menuItem_properties );
	
	menuEdit->AppendSeparator();
	
	wxMenuItem* menuItem_about;
	menuItem_about = new wxMenuItem( menuEdit, ID_MENUITEM_ABOUT, wxString( wxT("Über") ) , wxEmptyString, wxITEM_NORMAL );
	menuEdit->Append( menuItem_about );
	
	m_menubar1->Append( menuEdit, wxT("Bearbeiten") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxVERTICAL );
	
	m_panel29 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter3 = new wxSplitterWindow( m_panel29, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_NO_XP_THEME|wxNO_BORDER );
	m_splitter3->SetSashGravity( 1 );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter3OnIdle ), NULL, this );
	m_splitter3->SetMinimumPaneSize( 50 );
	
	m_panel121 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizer_displays;
	sizer_displays = new wxBoxSizer( wxHORIZONTAL );
	
	panel_sin = new wxPanel( m_panel121, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	panel_sin->SetBackgroundColour( wxColour( 32, 32, 32 ) );
	
	wxBoxSizer* sizer_sin;
	sizer_sin = new wxBoxSizer( wxVERTICAL );
	
	wxString choice_display_leftChoices[] = { wxT("Sinogramm"), wxT("Sinogramm (gefiltert, Ramp)"), wxT("Rekonstruktion (gefilterte Rückprojektion, Ramp)"), wxT("Rekonstruktion (ungefilterte Rückprojektion)") };
	int choice_display_leftNChoices = sizeof( choice_display_leftChoices ) / sizeof( wxString );
	choice_display_left = new wxChoice( panel_sin, wxID_ANY, wxDefaultPosition, wxDefaultSize, choice_display_leftNChoices, choice_display_leftChoices, 0|wxNO_BORDER );
	choice_display_left->SetSelection( 0 );
	choice_display_left->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	choice_display_left->SetForegroundColour( wxColour( 255, 255, 255 ) );
	choice_display_left->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	sizer_sin->Add( choice_display_left, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* sizer_sin_display;
	sizer_sin_display = new wxBoxSizer( wxHORIZONTAL );
	
	image_sinogram = new wxPanel( panel_sin, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	image_sinogram->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	sizer_sin_display->Add( image_sinogram, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0 );
	
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText69 = new wxStaticText( panel_sin, wxID_ANY, wxT("W"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	m_staticText69->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer58->Add( m_staticText69, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	slider_left_top = new wxSlider( panel_sin, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_LEFT|wxSL_VERTICAL );
	bSizer58->Add( slider_left_top, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
	
	slider_left_bottom = new wxSlider( panel_sin, wxID_ANY, 100, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_LEFT|wxSL_VERTICAL );
	bSizer58->Add( slider_left_bottom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
	
	
	sizer_sin_display->Add( bSizer58, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sizer_sin->Add( sizer_sin_display, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 0 );
	
	
	panel_sin->SetSizer( sizer_sin );
	panel_sin->Layout();
	sizer_sin->Fit( panel_sin );
	sizer_displays->Add( panel_sin, 1, wxEXPAND | wxALL, 1 );
	
	panel_rec = new wxPanel( m_panel121, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	panel_rec->SetBackgroundColour( wxColour( 32, 32, 32 ) );
	
	wxBoxSizer* sizer_rec;
	sizer_rec = new wxBoxSizer( wxVERTICAL );
	
	wxString choice_display_rightChoices[] = { wxT("Sinogramm"), wxT("Sinogram (gefiltert, Ramp)"), wxT("Rekonstruktion (gefilterte Rückprojektion, Ramp)"), wxT("Rekonstruktion (ungefilterte Rückprojektion)") };
	int choice_display_rightNChoices = sizeof( choice_display_rightChoices ) / sizeof( wxString );
	choice_display_right = new wxChoice( panel_rec, wxID_ANY, wxDefaultPosition, wxDefaultSize, choice_display_rightNChoices, choice_display_rightChoices, 0 );
	choice_display_right->SetSelection( 3 );
	choice_display_right->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	choice_display_right->SetForegroundColour( wxColour( 255, 255, 255 ) );
	choice_display_right->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	sizer_rec->Add( choice_display_right, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* sizer_rec_display;
	sizer_rec_display = new wxBoxSizer( wxHORIZONTAL );
	
	image_reconstruction = new wxPanel( panel_rec, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	image_reconstruction->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	sizer_rec_display->Add( image_reconstruction, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0 );
	
	wxBoxSizer* bSizer581;
	bSizer581 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText691 = new wxStaticText( panel_rec, wxID_ANY, wxT("W"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText691->Wrap( -1 );
	m_staticText691->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer581->Add( m_staticText691, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	slider_right_top = new wxSlider( panel_rec, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_LEFT|wxSL_VERTICAL );
	bSizer581->Add( slider_right_top, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
	
	slider_right_bottom = new wxSlider( panel_rec, wxID_ANY, 100, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_LEFT|wxSL_VERTICAL );
	bSizer581->Add( slider_right_bottom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
	
	
	sizer_rec_display->Add( bSizer581, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sizer_rec->Add( sizer_rec_display, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 0 );
	
	
	panel_rec->SetSizer( sizer_rec );
	panel_rec->Layout();
	sizer_rec->Fit( panel_rec );
	sizer_displays->Add( panel_rec, 1, wxEXPAND | wxALL, 1 );
	
	
	m_panel121->SetSizer( sizer_displays );
	m_panel121->Layout();
	sizer_displays->Fit( m_panel121 );
	m_panel301 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );
	
	m_notebook1 = new wxNotebook( m_panel301, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_NOPAGETHEME );
	panel_measurement_display = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 4, 0, 0 );
	
	m_panel261 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel261->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer90;
	bSizer90 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText67 = new wxStaticText( m_panel261, wxID_ANY, wxT("Dauer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText67->Wrap( -1 );
	m_staticText67->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer90->Add( m_staticText67, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer90->Add( 0, 0, 5, wxEXPAND, 5 );
	
	staticText_label_duration = new wxStaticText( m_panel261, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_duration->Wrap( -1 );
	staticText_label_duration->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer90->Add( staticText_label_duration, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer90->Add( 0, 0, 5, wxEXPAND, 5 );
	
	
	m_panel261->SetSizer( bSizer90 );
	m_panel261->Layout();
	bSizer90->Fit( m_panel261 );
	gSizer1->Add( m_panel261, 1, wxEXPAND | wxALL, 1 );
	
	m_panel2611 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2611->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer901;
	bSizer901 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText671 = new wxStaticText( m_panel2611, wxID_ANY, wxT("Röntgenparameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText671->Wrap( -1 );
	m_staticText671->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer901->Add( m_staticText671, 0, wxALL, 5 );
	
	
	bSizer901->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_xraydev = new wxStaticText( m_panel2611, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_xraydev->Wrap( -1 );
	staticText_label_xraydev->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	staticText_label_xraydev->Hide();
	
	bSizer901->Add( staticText_label_xraydev, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxHORIZONTAL );
	
	tc_voltage = new wxTextCtrl( m_panel2611, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT|wxNO_BORDER );
	tc_voltage->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	tc_voltage->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	tc_voltage->SetMinSize( wxSize( 0,-1 ) );
	
	bSizer87->Add( tc_voltage, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText157 = new wxStaticText( m_panel2611, wxID_ANY, wxT("kV  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText157->Wrap( -1 );
	m_staticText157->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer87->Add( m_staticText157, 0, wxALL|wxALIGN_BOTTOM, 2 );
	
	tc_current = new wxTextCtrl( m_panel2611, wxID_ANY, wxT("0.00"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT|wxNO_BORDER );
	tc_current->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	tc_current->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	tc_current->SetMinSize( wxSize( 0,-1 ) );
	
	bSizer87->Add( tc_current, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1571 = new wxStaticText( m_panel2611, wxID_ANY, wxT("mA"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1571->Wrap( -1 );
	m_staticText1571->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer87->Add( m_staticText1571, 0, wxALL|wxALIGN_BOTTOM, 2 );
	
	
	bSizer87->Add( 10, 0, 0, wxEXPAND, 0 );
	
	
	bSizer901->Add( bSizer87, 1, wxEXPAND, 5 );
	
	
	bSizer901->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel2611->SetSizer( bSizer901 );
	m_panel2611->Layout();
	bSizer901->Fit( m_panel2611 );
	gSizer1->Add( m_panel2611, 1, wxEXPAND | wxALL, 1 );
	
	m_panel2612 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2612->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer902;
	bSizer902 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText672 = new wxStaticText( m_panel2612, wxID_ANY, wxT("Impulse (letzter Wert)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText672->Wrap( -1 );
	m_staticText672->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer902->Add( m_staticText672, 0, wxALL, 5 );
	
	
	bSizer902->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_counts = new wxStaticText( m_panel2612, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_counts->Wrap( -1 );
	staticText_label_counts->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer902->Add( staticText_label_counts, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer902->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel2612->SetSizer( bSizer902 );
	m_panel2612->Layout();
	bSizer902->Fit( m_panel2612 );
	gSizer1->Add( m_panel2612, 1, wxEXPAND | wxALL, 1 );
	
	m_panel26151 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel26151->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer9051;
	bSizer9051 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText6751 = new wxStaticText( m_panel26151, wxID_ANY, wxT("Gerätestatus"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6751->Wrap( -1 );
	m_staticText6751->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9051->Add( m_staticText6751, 0, wxALL, 5 );
	
	
	bSizer9051->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_statard
	= new wxStaticText( m_panel26151, wxID_ANY, wxT("ARD ERROR"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_statard
	->Wrap( -1 );
	staticText_label_statard
	->SetFont( wxFont( 15, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9051->Add( staticText_label_statard
	, 0, wxALL|wxEXPAND, 5 );
	
	staticText_label_statxraydev = new wxStaticText( m_panel26151, wxID_ANY, wxT("XRAY ERROR"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_statxraydev->Wrap( -1 );
	staticText_label_statxraydev->SetFont( wxFont( 15, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9051->Add( staticText_label_statxraydev, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer9051->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel26151->SetSizer( bSizer9051 );
	m_panel26151->Layout();
	bSizer9051->Fit( m_panel26151 );
	gSizer1->Add( m_panel26151, 1, wxEXPAND | wxALL, 1 );
	
	m_panel2613 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2613->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer903;
	bSizer903 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText673 = new wxStaticText( m_panel2613, wxID_ANY, wxT("Fortschritt"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText673->Wrap( -1 );
	m_staticText673->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer903->Add( m_staticText673, 0, wxALL, 5 );
	
	
	bSizer903->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_progress = new wxStaticText( m_panel2613, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_progress->Wrap( -1 );
	staticText_label_progress->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer903->Add( staticText_label_progress, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer903->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel2613->SetSizer( bSizer903 );
	m_panel2613->Layout();
	bSizer903->Fit( m_panel2613 );
	gSizer1->Add( m_panel2613, 1, wxEXPAND | wxALL, 1 );
	
	m_panel2614 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2614->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer904;
	bSizer904 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText674 = new wxStaticText( m_panel2614, wxID_ANY, wxT("Transversale Position"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText674->Wrap( -1 );
	m_staticText674->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer92->Add( m_staticText674, 0, wxALL, 5 );
	
	
	bSizer92->Add( 0, 0, 1, wxEXPAND, 5 );
	
	button_set_min_trans = new wxButton( m_panel2614, wxID_ANY, wxT("min"), wxDefaultPosition, wxSize( 30,20 ), 0 );
	button_set_min_trans->SetToolTip( wxT("Setze aktuellen Wert als transversalen Startwert T1") );
	
	bSizer92->Add( button_set_min_trans, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	button_set_max_trans = new wxButton( m_panel2614, wxID_ANY, wxT("max"), wxDefaultPosition, wxSize( 30,20 ), 0 );
	button_set_max_trans->SetToolTip( wxT("Setze aktuellen Wert als transversalen Endwert T2") );
	
	bSizer92->Add( button_set_max_trans, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	
	bSizer904->Add( bSizer92, 0, wxEXPAND, 5 );
	
	
	bSizer904->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_tpos = new wxStaticText( m_panel2614, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_tpos->Wrap( -1 );
	staticText_label_tpos->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	staticText_label_tpos->Hide();
	
	bSizer904->Add( staticText_label_tpos, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxHORIZONTAL );
	
	tc_trans_pos = new wxTextCtrl( m_panel2614, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT|wxNO_BORDER );
	tc_trans_pos->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	tc_trans_pos->SetBackgroundColour( wxColour( 254, 248, 211 ) );
	
	bSizer86->Add( tc_trans_pos, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText162 = new wxStaticText( m_panel2614, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText162->Wrap( -1 );
	m_staticText162->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer86->Add( m_staticText162, 0, wxALL|wxALIGN_BOTTOM, 2 );
	
	
	bSizer86->Add( 10, 0, 0, wxEXPAND, 0 );
	
	
	bSizer904->Add( bSizer86, 1, wxEXPAND, 5 );
	
	
	bSizer904->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel2614->SetSizer( bSizer904 );
	m_panel2614->Layout();
	bSizer904->Fit( m_panel2614 );
	gSizer1->Add( m_panel2614, 1, wxEXPAND | wxALL, 1 );
	
	m_panel2615 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2615->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer905;
	bSizer905 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText675 = new wxStaticText( m_panel2615, wxID_ANY, wxT("Azimutale Position"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText675->Wrap( -1 );
	m_staticText675->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer93->Add( m_staticText675, 0, wxALL, 5 );
	
	
	bSizer93->Add( 0, 0, 1, wxEXPAND, 5 );
	
	button_set_min_azimu = new wxButton( m_panel2615, wxID_ANY, wxT("min"), wxDefaultPosition, wxSize( 30,20 ), 0 );
	button_set_min_azimu->SetToolTip( wxT("Setze aktuellen Wert als azimutalen Startwert A1") );
	
	bSizer93->Add( button_set_min_azimu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	button_set_max_azimu = new wxButton( m_panel2615, wxID_ANY, wxT("max"), wxDefaultPosition, wxSize( 30,20 ), 0 );
	button_set_max_azimu->SetToolTip( wxT("Setze aktuellen Wert als azimutalen Endwert A2") );
	
	bSizer93->Add( button_set_max_azimu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	
	bSizer905->Add( bSizer93, 0, wxEXPAND, 5 );
	
	
	bSizer905->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_apos = new wxStaticText( m_panel2615, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_apos->Wrap( -1 );
	staticText_label_apos->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	staticText_label_apos->Hide();
	
	bSizer905->Add( staticText_label_apos, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer94;
	bSizer94 = new wxBoxSizer( wxHORIZONTAL );
	
	tc_azimu_pos = new wxTextCtrl( m_panel2615, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT|wxNO_BORDER );
	tc_azimu_pos->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	tc_azimu_pos->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer94->Add( tc_azimu_pos, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1621 = new wxStaticText( m_panel2615, wxID_ANY, wxT("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1621->Wrap( -1 );
	m_staticText1621->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer94->Add( m_staticText1621, 0, wxALL|wxALIGN_BOTTOM, 2 );
	
	
	bSizer94->Add( 10, 0, 0, wxEXPAND, 0 );
	
	
	bSizer905->Add( bSizer94, 1, wxEXPAND, 5 );
	
	
	bSizer905->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel2615->SetSizer( bSizer905 );
	m_panel2615->Layout();
	bSizer905->Fit( m_panel2615 );
	gSizer1->Add( m_panel2615, 1, wxEXPAND | wxALL, 1 );
	
	m_panel26152 = new wxPanel( panel_measurement_display, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel26152->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	wxBoxSizer* bSizer9052;
	bSizer9052 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText6752 = new wxStaticText( m_panel26152, wxID_ANY, wxT("Tomographie"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6752->Wrap( -1 );
	m_staticText6752->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9052->Add( m_staticText6752, 0, wxALL, 5 );
	
	
	bSizer9052->Add( 0, 0, 1, wxEXPAND, 5 );
	
	staticText_label_tomography
	= new wxStaticText( m_panel26152, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_label_tomography
	->Wrap( -1 );
	staticText_label_tomography
	->SetFont( wxFont( 20, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9052->Add( staticText_label_tomography
	, 0, wxALL, 5 );
	
	
	bSizer9052->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel26152->SetSizer( bSizer9052 );
	m_panel26152->Layout();
	bSizer9052->Fit( m_panel26152 );
	gSizer1->Add( m_panel26152, 1, wxEXPAND | wxALL, 1 );
	
	
	panel_measurement_display->SetSizer( gSizer1 );
	panel_measurement_display->Layout();
	gSizer1->Fit( panel_measurement_display );
	m_notebook1->AddPage( panel_measurement_display, wxT("Status"), true );
	m_panel26 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer72->Add( 0, 5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer77;
	bSizer77 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4111;
	bSizer4111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2621 = new wxStaticText( m_panel26, wxID_ANY, wxT("Vorwärtsprojektion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2621->Wrap( -1 );
	m_staticText2621->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer4111->Add( m_staticText2621, 0, wxALL, 5 );
	
	m_staticline311 = new wxStaticLine( m_panel26, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4111->Add( m_staticline311, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer62->Add( bSizer4111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );
	
	button_fwp = new wxButton( m_panel26, ID_BUTTON_FWP, wxT("Berechnen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer68->Add( button_fwp, 0, wxALL, 5 );
	
	m_staticText43 = new wxStaticText( m_panel26, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	m_staticText43->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer68->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_status_fwp = new wxStaticText( m_panel26, wxID_ANY, wxT("Nicht berechnet"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_status_fwp->Wrap( -1 );
	bSizer68->Add( staticText_status_fwp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer62->Add( bSizer68, 0, wxEXPAND, 5 );
	
	
	bSizer62->Add( 0, 5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41111;
	bSizer41111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText26211 = new wxStaticText( m_panel26, wxID_ANY, wxT("Gefilterte Rückprojektion (FBP)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26211->Wrap( -1 );
	m_staticText26211->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer41111->Add( m_staticText26211, 0, wxALL, 5 );
	
	m_staticline3111 = new wxStaticLine( m_panel26, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer41111->Add( m_staticline3111, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer62->Add( bSizer41111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer681;
	bSizer681 = new wxBoxSizer( wxHORIZONTAL );
	
	button_fbp = new wxButton( m_panel26, ID_BUTTON_FBP, wxT("Berechnen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer681->Add( button_fbp, 0, wxALL, 5 );
	
	m_staticText431 = new wxStaticText( m_panel26, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	bSizer681->Add( m_staticText431, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_status_fbp = new wxStaticText( m_panel26, wxID_ANY, wxT("Nicht berechnet"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_status_fbp->Wrap( -1 );
	bSizer681->Add( staticText_status_fbp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer62->Add( bSizer681, 0, wxEXPAND, 5 );
	
	
	bSizer62->Add( 0, 5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer411111;
	bSizer411111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText262111 = new wxStaticText( m_panel26, wxID_ANY, wxT("Ungefilterte Rückprojektion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText262111->Wrap( -1 );
	m_staticText262111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer411111->Add( m_staticText262111, 0, wxALL, 5 );
	
	m_staticline31111 = new wxStaticLine( m_panel26, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer411111->Add( m_staticline31111, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer62->Add( bSizer411111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer682;
	bSizer682 = new wxBoxSizer( wxHORIZONTAL );
	
	button_bp = new wxButton( m_panel26, ID_BUTTON_BP, wxT("Berechnen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer682->Add( button_bp, 0, wxALL, 5 );
	
	m_staticText432 = new wxStaticText( m_panel26, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText432->Wrap( -1 );
	bSizer682->Add( m_staticText432, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_status_bp = new wxStaticText( m_panel26, wxID_ANY, wxT("Nicht berechnet"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_status_bp->Wrap( -1 );
	bSizer682->Add( staticText_status_bp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer62->Add( bSizer682, 0, wxEXPAND, 5 );
	
	
	bSizer77->Add( bSizer62, 1, wxEXPAND, 5 );
	
	
	bSizer77->Add( 25, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer621;
	bSizer621 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer41112;
	bSizer41112 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText26212 = new wxStaticText( m_panel26, wxID_ANY, wxT("Iterative ART"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26212->Wrap( -1 );
	m_staticText26212->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	m_staticText26212->Hide();
	
	bSizer41112->Add( m_staticText26212, 0, wxALL, 5 );
	
	m_staticline3112 = new wxStaticLine( m_panel26, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_staticline3112->Hide();
	
	bSizer41112->Add( m_staticline3112, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer621->Add( bSizer41112, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer683;
	bSizer683 = new wxBoxSizer( wxHORIZONTAL );
	
	button_iart = new wxButton( m_panel26, wxID_ANY, wxT("Berechnen"), wxDefaultPosition, wxDefaultSize, 0 );
	button_iart->Hide();
	
	bSizer683->Add( button_iart, 0, wxALL, 5 );
	
	m_staticText433 = new wxStaticText( m_panel26, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText433->Wrap( -1 );
	m_staticText433->Hide();
	
	bSizer683->Add( m_staticText433, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_status_iart = new wxStaticText( m_panel26, wxID_ANY, wxT("Nicht berechnet"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_status_iart->Wrap( -1 );
	staticText_status_iart->Hide();
	
	bSizer683->Add( staticText_status_iart, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer621->Add( bSizer683, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer811;
	bSizer811 = new wxBoxSizer( wxHORIZONTAL );
	
	button_tp_set = new wxButton( m_panel26, wxID_ANY, wxT("Drehpunkt setzen"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer811->Add( button_tp_set, 0, wxALL, 5 );
	
	textC_tp = new wxTextCtrl( m_panel26, wxID_ANY, wxT("0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer811->Add( textC_tp, 0, wxALL, 5 );
	
	m_staticText136 = new wxStaticText( m_panel26, wxID_ANY, wxT("Detektorpos\n(relativ, 0-1)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText136->Wrap( -1 );
	bSizer811->Add( m_staticText136, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer621->Add( bSizer811, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8111;
	bSizer8111 = new wxBoxSizer( wxHORIZONTAL );
	
	button_i0_set = new wxButton( m_panel26, wxID_ANY, wxT("I_0 Impulse setzen"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer8111->Add( button_i0_set, 0, wxALL, 5 );
	
	textC_i0 = new wxTextCtrl( m_panel26, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8111->Add( textC_i0, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1361 = new wxStaticText( m_panel26, wxID_ANY, wxT("Impulse \n(1 deakt.)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1361->Wrap( -1 );
	bSizer8111->Add( m_staticText1361, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer621->Add( bSizer8111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8112;
	bSizer8112 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText140 = new wxStaticText( m_panel26, wxID_ANY, wxT("Tote Pixel auslassen"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	m_staticText140->Wrap( -1 );
	bSizer8112->Add( m_staticText140, 0, wxALL, 5 );
	
	m_checkBox1 = new wxCheckBox( m_panel26, wxID_ANY, wxT(" (Lineare Interpolation von betroffenen Pixeln)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8112->Add( m_checkBox1, 0, wxALL, 5 );
	
	
	bSizer621->Add( bSizer8112, 1, wxEXPAND, 5 );
	
	
	bSizer621->Add( 0, 15, 1, wxEXPAND, 5 );
	
	
	bSizer77->Add( bSizer621, 1, wxEXPAND, 5 );
	
	
	bSizer72->Add( bSizer77, 1, wxEXPAND, 5 );
	
	
	m_panel26->SetSizer( bSizer72 );
	m_panel26->Layout();
	bSizer72->Fit( m_panel26 );
	m_notebook1->AddPage( m_panel26, wxT("Tomographische Berechnungen"), false );
	
	bSizer59->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );
	
	m_panel271 = new wxPanel( m_panel301, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel271->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer881;
	bSizer881 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1482 = new wxStaticText( m_panel271, wxID_ANY, wxT("XRAY Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1482->Wrap( -1 );
	m_staticText1482->SetFont( wxFont( 10, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer881->Add( m_staticText1482, 0, wxALL, 5 );
	
	
	bSizer881->Add( 0, 0, 1, wxEXPAND, 5 );
	
	st_xray_status = new wxStaticText( m_panel271, wxID_ANY, wxT("OFF"), wxDefaultPosition, wxDefaultSize, 0 );
	st_xray_status->Wrap( -1 );
	st_xray_status->SetFont( wxFont( 20, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer881->Add( st_xray_status, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer881->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel271->SetSizer( bSizer881 );
	m_panel271->Layout();
	bSizer881->Fit( m_panel271 );
	bSizer64->Add( m_panel271, 1, wxEXPAND | wxALL, 1 );
	
	m_panel27 = new wxPanel( m_panel301, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel27->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText148 = new wxStaticText( m_panel27, wxID_ANY, wxT("Manuell"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText148->Wrap( -1 );
	m_staticText148->SetFont( wxFont( 10, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer88->Add( m_staticText148, 0, wxALL, 5 );
	
	button_man_xray = new wxButton( m_panel27, wxID_ANY, wxT("XRAY on"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer88->Add( button_man_xray, 0, wxALL|wxEXPAND, 5 );
	
	button_drive_motor = new wxButton( m_panel27, wxID_ANY, wxT("Motor fahren"), wxDefaultPosition, wxDefaultSize, 0 );
	button_drive_motor->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer88->Add( button_drive_motor, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel27->SetSizer( bSizer88 );
	m_panel27->Layout();
	bSizer88->Fit( m_panel27 );
	bSizer64->Add( m_panel27, 1, wxEXPAND | wxALL, 1 );
	
	m_panel28 = new wxPanel( m_panel301, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel28->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer906;
	bSizer906 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1481 = new wxStaticText( m_panel28, wxID_ANY, wxT("Messung"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1481->Wrap( -1 );
	m_staticText1481->SetFont( wxFont( 10, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer906->Add( m_staticText1481, 0, wxALL, 5 );
	
	button_shot = new wxButton( m_panel28, ID_BUTTON_SHOT, wxT("Neue Messung"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	button_shot->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	button_shot->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	bSizer906->Add( button_shot, 0, wxALL|wxEXPAND, 5 );
	
	button_stop = new wxButton( m_panel28, ID_BUTTON_STOP, wxT("Stoppen"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer906->Add( button_stop, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel28->SetSizer( bSizer906 );
	m_panel28->Layout();
	bSizer906->Fit( m_panel28 );
	bSizer64->Add( m_panel28, 1, wxEXPAND | wxALL, 1 );
	
	
	bSizer59->Add( bSizer64, 0, wxEXPAND, 0 );
	
	
	m_panel301->SetSizer( bSizer59 );
	m_panel301->Layout();
	bSizer59->Fit( m_panel301 );
	m_splitter3->SplitHorizontally( m_panel121, m_panel301, 0 );
	bSizer39->Add( m_splitter3, 1, wxEXPAND, 5 );
	
	m_panel18 = new wxPanel( m_panel29, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer39->Add( m_panel18, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxVERTICAL );
	
	panel_gauges = new wxPanel( m_panel29, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxTAB_TRAVERSAL );
	panel_gauges->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	wxBoxSizer* bSizer461;
	bSizer461 = new wxBoxSizer( wxVERTICAL );
	
	panel_gauge_comp = new wxPanel( panel_gauges, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	panel_gauge_comp->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	
	wxBoxSizer* Sizer_comp;
	Sizer_comp = new wxBoxSizer( wxVERTICAL );
	
	Sizer_comp->SetMinSize( wxSize( 100,4 ) ); 
	
	panel_gauge_comp->SetSizer( Sizer_comp );
	panel_gauge_comp->Layout();
	Sizer_comp->Fit( panel_gauge_comp );
	bSizer461->Add( panel_gauge_comp, 0, wxALL, 0 );
	
	panel_gauge_meas = new wxPanel( panel_gauges, wxID_ANY, wxDefaultPosition, wxSize( 200,4 ), wxTAB_TRAVERSAL );
	panel_gauge_meas->SetBackgroundColour( wxColour( 0, 0, 255 ) );
	
	wxBoxSizer* sizer_meas;
	sizer_meas = new wxBoxSizer( wxVERTICAL );
	
	sizer_meas->SetMinSize( wxSize( 500,4 ) ); 
	
	panel_gauge_meas->SetSizer( sizer_meas );
	panel_gauge_meas->Layout();
	bSizer461->Add( panel_gauge_meas, 0, wxALL, 0 );
	
	
	panel_gauges->SetSizer( bSizer461 );
	panel_gauges->Layout();
	bSizer461->Fit( panel_gauges );
	bSizer48->Add( panel_gauges, 0, wxALL|wxEXPAND, 0 );
	
	
	bSizer39->Add( bSizer48, 0, wxEXPAND, 0 );
	
	
	m_panel29->SetSizer( bSizer39 );
	m_panel29->Layout();
	bSizer39->Fit( m_panel29 );
	bSizer56->Add( m_panel29, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer56 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::on_Close ) );
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::on_key_down ) );
	this->Connect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::on_key_up ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::on_mainframe_size_event ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::on_mainframe_size_event ) );
	this->Connect( menuItem_loadsino->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_loadsino_pressed ) );
	this->Connect( menuItem_savesino->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_savesino_pressed ) );
	this->Connect( menuItem_savereco->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_savereco_pressed ) );
	this->Connect( menuItem_exportdata->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_exportdata_pressed ) );
	this->Connect( menuItem_exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_exit_pressed ) );
	this->Connect( menuItem_properties->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_properties_pressed ) );
	this->Connect( menuItem_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_about_pressed ) );
	m_splitter3->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( MainFrame::on_sash_position_changed ), NULL, this );
	m_splitter3->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, wxSplitterEventHandler( MainFrame::on_sash_position_changed ), NULL, this );
	choice_display_left->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::on_choice_display_left_pressed ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	choice_display_right->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::on_choice_display_right_pressed ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	button_set_min_trans->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_min_trans_pressed ), NULL, this );
	button_set_max_trans->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_max_trans_pressed ), NULL, this );
	button_set_min_azimu->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_min_azimu_pressed ), NULL, this );
	button_set_max_azimu->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_max_azimu_pressed ), NULL, this );
	button_fwp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_fwp_pressed ), NULL, this );
	button_fbp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_fbp_pressed ), NULL, this );
	button_bp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_bp_pressed ), NULL, this );
	button_tp_set->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_tp_set_pressed ), NULL, this );
	button_i0_set->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_i0_set_pressed ), NULL, this );
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::on_deadpixel_checkbox_clicked ), NULL, this );
	button_man_xray->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_man_xray_pressed ), NULL, this );
	button_drive_motor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_drive_motor_pressed ), NULL, this );
	button_shot->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_shot_pressed ), NULL, this );
	button_stop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_stop_pressed ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::on_Close ) );
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::on_key_down ) );
	this->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::on_key_up ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::on_mainframe_size_event ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::on_mainframe_size_event ) );
	this->Disconnect( ID_MENUITEM_LOADSINO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_loadsino_pressed ) );
	this->Disconnect( ID_MENUITEM_SAVESINO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_savesino_pressed ) );
	this->Disconnect( ID_MENUITEM_SAVERECO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_savereco_pressed ) );
	this->Disconnect( ID_MENUITEM_EXPORTDATA, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_exportdata_pressed ) );
	this->Disconnect( ID_MENUITEM_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_exit_pressed ) );
	this->Disconnect( ID_MENUITEM_PROPERTIES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_properties_pressed ) );
	this->Disconnect( ID_MENUITEM_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::on_menuItem_about_pressed ) );
	m_splitter3->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( MainFrame::on_sash_position_changed ), NULL, this );
	m_splitter3->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, wxSplitterEventHandler( MainFrame::on_sash_position_changed ), NULL, this );
	choice_display_left->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::on_choice_display_left_pressed ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_top->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_left_top_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	slider_left_bottom->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_left_bottom_scroll ), NULL, this );
	choice_display_right->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::on_choice_display_right_pressed ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_top->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_right_top_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	slider_right_bottom->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::on_slider_right_bottom_scroll ), NULL, this );
	button_set_min_trans->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_min_trans_pressed ), NULL, this );
	button_set_max_trans->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_max_trans_pressed ), NULL, this );
	button_set_min_azimu->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_min_azimu_pressed ), NULL, this );
	button_set_max_azimu->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_set_max_azimu_pressed ), NULL, this );
	button_fwp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_fwp_pressed ), NULL, this );
	button_fbp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_fbp_pressed ), NULL, this );
	button_bp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_bp_pressed ), NULL, this );
	button_tp_set->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_tp_set_pressed ), NULL, this );
	button_i0_set->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_i0_set_pressed ), NULL, this );
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::on_deadpixel_checkbox_clicked ), NULL, this );
	button_man_xray->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_man_xray_pressed ), NULL, this );
	button_drive_motor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_drive_motor_pressed ), NULL, this );
	button_shot->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_shot_pressed ), NULL, this );
	button_stop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::on_button_stop_pressed ), NULL, this );
	
}

MyDialog2::MyDialog2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );
	
	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	m_gauge1->SetValue( 40 ); 
	bSizer75->Add( m_gauge1, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer75 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

MyDialog2::~MyDialog2()
{
}

PropertyDialog::PropertyDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	prop_panel_xraydev = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText47 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Hinweis: Port-Pfad vollständig angeben, z.B. :  \\\\.\\COM4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	bSizer68->Add( m_staticText47, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("COM Port"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText45->Wrap( -1 );
	bSizer72->Add( m_staticText45, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	textCtrl_comport_xraydev = new wxTextCtrl( prop_panel_xraydev, wxID_ANY, wxT("\\\\.\\COM4"), wxDefaultPosition, wxDefaultSize, 0 );
	textCtrl_comport_xraydev->SetMaxLength( 10 ); 
	bSizer72->Add( textCtrl_comport_xraydev, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	button_testcom_xraydev = new wxButton( prop_panel_xraydev, ID_BUTTON_TESTCOM_XRAYDEV, wxT("Verbinden"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( button_testcom_xraydev, 0, wxALL, 5 );
	
	
	bSizer68->Add( bSizer72, 0, wxEXPAND, 5 );
	
	
	bSizer68->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticline181 = new wxStaticLine( prop_panel_xraydev, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer68->Add( m_staticline181, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer1081;
	bSizer1081 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer981;
	bSizer981 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1472 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Timing (serielle Verbindung)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1472->Wrap( -1 );
	m_staticText1472->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer981->Add( m_staticText1472, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer981->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1081->Add( bSizer981, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72114;
	bSizer72114 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45214 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Service_Restart_Delay"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText45214->Wrap( -1 );
	m_staticText45214->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer72114->Add( m_staticText45214, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_xray_service_restart = new wxTextCtrl( prop_panel_xraydev, wxID_ANY, wxT("15"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72114->Add( tc_tim_xray_service_restart, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1512 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1512->Wrap( -1 );
	bSizer72114->Add( m_staticText1512, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1081->Add( bSizer72114, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer721111;
	bSizer721111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText452111 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Serial_Read_Timeout"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText452111->Wrap( -1 );
	bSizer721111->Add( m_staticText452111, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_xray_read_timeout = new wxTextCtrl( prop_panel_xraydev, wxID_ANY, wxT("250"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer721111->Add( tc_tim_xray_read_timeout, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText15112 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15112->Wrap( -1 );
	bSizer721111->Add( m_staticText15112, 0, wxALL, 5 );
	
	
	bSizer1081->Add( bSizer721111, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer721121;
	bSizer721121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText452121 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Serial_Write_Timeout"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText452121->Wrap( -1 );
	bSizer721121->Add( m_staticText452121, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_xray_write_timeout = new wxTextCtrl( prop_panel_xraydev, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer721121->Add( tc_tim_xray_write_timeout, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText151112 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText151112->Wrap( -1 );
	bSizer721121->Add( m_staticText151112, 0, wxALL, 5 );
	
	
	bSizer1081->Add( bSizer721121, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer721131;
	bSizer721131 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText452131 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Next_Message_Delay"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText452131->Wrap( -1 );
	bSizer721131->Add( m_staticText452131, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_xray_message_delay = new wxTextCtrl( prop_panel_xraydev, wxID_ANY, wxT("25"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer721131->Add( tc_tim_xray_message_delay, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1511111 = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1511111->Wrap( -1 );
	bSizer721131->Add( m_staticText1511111, 0, wxALL, 5 );
	
	
	bSizer1081->Add( bSizer721131, 1, wxEXPAND, 5 );
	
	
	bSizer68->Add( bSizer1081, 0, wxEXPAND, 5 );
	
	m_staticline13 = new wxStaticLine( prop_panel_xraydev, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer68->Add( m_staticline13, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer5912;
	bSizer5912 = new wxBoxSizer( wxVERTICAL );
	
	staticText_info_xraydev = new wxStaticText( prop_panel_xraydev, wxID_ANY, wxT("Keine Informationen vorhanden."), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_info_xraydev->Wrap( -1 );
	staticText_info_xraydev->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5912->Add( staticText_info_xraydev, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer68->Add( bSizer5912, 1, wxEXPAND, 5 );
	
	
	bSizer68->Add( 0, 15, 1, wxEXPAND, 5 );
	
	
	bSizer81->Add( bSizer68, 1, wxEXPAND, 10 );
	
	
	prop_panel_xraydev->SetSizer( bSizer81 );
	prop_panel_xraydev->Layout();
	bSizer81->Fit( prop_panel_xraydev );
	m_notebook2->AddPage( prop_panel_xraydev, wxT("PHYWE Röntgengerät"), false );
	prop_panel_arduino = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText471 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Hinweis: Port-Pfad vollständig angeben, z.B. :  \\\\.\\COM1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText471->Wrap( -1 );
	bSizer69->Add( m_staticText471, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer721;
	bSizer721 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText452 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("COM Port"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText452->Wrap( -1 );
	bSizer721->Add( m_staticText452, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	textCtrl_comport_arduino = new wxTextCtrl( prop_panel_arduino, wxID_ANY, wxT("\\\\.\\COM1"), wxDefaultPosition, wxDefaultSize, 0 );
	textCtrl_comport_arduino->SetMaxLength( 10 ); 
	bSizer721->Add( textCtrl_comport_arduino, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	button_testcom_ardunio = new wxButton( prop_panel_arduino, ID_BUTTON_TESTCOM_ARDUINO, wxT("Verbinden"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer721->Add( button_testcom_ardunio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer69->Add( bSizer721, 0, wxEXPAND, 5 );
	
	
	bSizer69->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticline18 = new wxStaticLine( prop_panel_arduino, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer69->Add( m_staticline18, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer108;
	bSizer108 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText147 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Timing (serielle Verbindung)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText147->Wrap( -1 );
	m_staticText147->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer98->Add( m_staticText147, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer108->Add( bSizer98, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7211;
	bSizer7211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4521 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Service_Restart_Delay"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText4521->Wrap( -1 );
	m_staticText4521->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer7211->Add( m_staticText4521, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_ard_service_restart = new wxTextCtrl( prop_panel_arduino, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7211->Add( tc_tim_ard_service_restart, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText151 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText151->Wrap( -1 );
	bSizer7211->Add( m_staticText151, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer108->Add( bSizer7211, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72111;
	bSizer72111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45211 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Serial_Read_Timeout"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText45211->Wrap( -1 );
	bSizer72111->Add( m_staticText45211, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_ard_read_timeout = new wxTextCtrl( prop_panel_arduino, wxID_ANY, wxT("250"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72111->Add( tc_tim_ard_read_timeout, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1511 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1511->Wrap( -1 );
	bSizer72111->Add( m_staticText1511, 0, wxALL, 5 );
	
	
	bSizer108->Add( bSizer72111, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72112;
	bSizer72112 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45212 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Serial_Write_Timeout"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText45212->Wrap( -1 );
	bSizer72112->Add( m_staticText45212, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_ard_write_timeout = new wxTextCtrl( prop_panel_arduino, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72112->Add( tc_tim_ard_write_timeout, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText15111 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15111->Wrap( -1 );
	bSizer72112->Add( m_staticText15111, 0, wxALL, 5 );
	
	
	bSizer108->Add( bSizer72112, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72113;
	bSizer72113 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45213 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Next_Message_Delay"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText45213->Wrap( -1 );
	bSizer72113->Add( m_staticText45213, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_tim_ard_message_delay = new wxTextCtrl( prop_panel_arduino, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72113->Add( tc_tim_ard_message_delay, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText151111 = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText151111->Wrap( -1 );
	bSizer72113->Add( m_staticText151111, 0, wxALL, 5 );
	
	
	bSizer108->Add( bSizer72113, 1, wxEXPAND, 5 );
	
	
	bSizer69->Add( bSizer108, 0, wxEXPAND, 5 );
	
	m_staticline12 = new wxStaticLine( prop_panel_arduino, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer69->Add( m_staticline12, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer5911;
	bSizer5911 = new wxBoxSizer( wxVERTICAL );
	
	staticText_info_arduino = new wxStaticText( prop_panel_arduino, wxID_ANY, wxT("Keine Informationen vorhanden."), wxDefaultPosition, wxDefaultSize, 0 );
	staticText_info_arduino->Wrap( -1 );
	staticText_info_arduino->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5911->Add( staticText_info_arduino, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer69->Add( bSizer5911, 0, wxEXPAND, 5 );
	
	
	bSizer69->Add( 0, 15, 1, wxEXPAND, 5 );
	
	
	bSizer83->Add( bSizer69, 1, wxEXPAND, 10 );
	
	
	prop_panel_arduino->SetSizer( bSizer83 );
	prop_panel_arduino->Layout();
	bSizer83->Fit( prop_panel_arduino );
	m_notebook2->AddPage( prop_panel_arduino, wxT("Arduino"), true );
	
	bSizer65->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer771;
	bSizer771 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button19 = new wxButton( this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer771->Add( m_button19, 0, wxALL, 5 );
	
	m_button20 = new wxButton( this, wxID_CANCEL, wxT("Abbrechen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer771->Add( m_button20, 0, wxALL, 5 );
	
	
	bSizer65->Add( bSizer771, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer65 );
	this->Layout();
	bSizer65->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	button_testcom_xraydev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_testcom_xraydev_pressed ), NULL, this );
	button_testcom_ardunio->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_testcom_ardunio_pressed ), NULL, this );
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_ok_pressed ), NULL, this );
}

PropertyDialog::~PropertyDialog()
{
	// Disconnect Events
	button_testcom_xraydev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_testcom_xraydev_pressed ), NULL, this );
	button_testcom_ardunio->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_testcom_ardunio_pressed ), NULL, this );
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::on_button_ok_pressed ), NULL, this );
	
}

ConsoleFrame::ConsoleFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	m_panel15 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxVERTICAL );
	
	textCtrl_console = new wxTextCtrl( m_panel15, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer56->Add( textCtrl_console, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panel15->SetSizer( bSizer56 );
	m_panel15->Layout();
	bSizer56->Fit( m_panel15 );
	bSizer41->Add( m_panel15, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer41 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConsoleFrame::on_consoleframe_closed ) );
}

ConsoleFrame::~ConsoleFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConsoleFrame::on_consoleframe_closed ) );
	
}

MeasurementWizard::MeasurementWizard( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style ) 
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxWizardPageSimple* m_wizPage8 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage8 );
	
	wxBoxSizer* bSizer901;
	bSizer901 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer60111111;
	bSizer60111111 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText61111111111 = new wxStaticText( m_wizPage8, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText61111111111->Wrap( -1 );
	m_staticText61111111111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText61111111111->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer60111111->Add( m_staticText61111111111, 0, wxALL, 5 );
	
	m_staticText611211111 = new wxStaticText( m_wizPage8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText611211111->Wrap( -1 );
	bSizer60111111->Add( m_staticText611211111, 0, wxALL, 5 );
	
	m_staticText6111211111 = new wxStaticText( m_wizPage8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6111211111->Wrap( -1 );
	bSizer60111111->Add( m_staticText6111211111, 0, wxALL, 5 );
	
	
	bSizer901->Add( bSizer60111111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer601;
	bSizer601 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText6112 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Erfassungsbereich"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText6112->Wrap( -1 );
	m_staticText6112->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer601->Add( m_staticText6112, 0, wxALL, 5 );
	
	m_staticText61112 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Röntgenparameter"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText61112->Wrap( -1 );
	bSizer601->Add( m_staticText61112, 0, wxALL, 5 );
	
	m_staticText611111 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Einschalten"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText611111->Wrap( -1 );
	bSizer601->Add( m_staticText611111, 0, wxALL, 5 );
	
	
	bSizer901->Add( bSizer601, 0, wxEXPAND, 5 );
	
	m_staticline51 = new wxStaticLine( m_wizPage8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer901->Add( m_staticline51, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer901->Add( 15, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1031;
	bSizer1031 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridSizer* gSizer21;
	gSizer21 = new wxGridSizer( 0, 3, 0, 0 );
	
	m_staticText623 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Detektorzeilen"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText623->Wrap( -1 );
	gSizer21->Add( m_staticText623, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_detectorrows = new wxSpinButton( m_wizPage8, ID_SPIN_DETECTORROWS, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer21->Add( spin_detectorrows, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_detectorrows = new wxStaticText( m_wizPage8, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_detectorrows->Wrap( -1 );
	staticText_label_detectorrows->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_detectorrows, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6212 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Aufnahmewinkel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6212->Wrap( -1 );
	gSizer21->Add( m_staticText6212, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_angles = new wxSpinButton( m_wizPage8, ID_SPIN_ANGLES, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer21->Add( spin_angles, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_angles = new wxStaticText( m_wizPage8, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_angles->Wrap( -1 );
	staticText_label_angles->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_angles, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText181122 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Startpunkt T1"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181122->Wrap( -1 );
	gSizer21->Add( m_staticText181122, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_trans_min = new wxTextCtrl( m_wizPage8, ID_TEXT_TRANS_MIN, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_trans_min->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_trans_min, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText18111121 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("mm"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18111121->Wrap( -1 );
	gSizer21->Add( m_staticText18111121, 0, wxALL, 5 );
	
	m_staticText1811213 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Endpunkt T2"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811213->Wrap( -1 );
	gSizer21->Add( m_staticText1811213, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_trans_max = new wxTextCtrl( m_wizPage8, ID_TEXT_TRANS_MAX, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_trans_max->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_trans_max, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText181111131 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("mm"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181111131->Wrap( -1 );
	gSizer21->Add( m_staticText181111131, 0, wxALL, 5 );
	
	m_staticText18112111 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Startpunkt A1"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18112111->Wrap( -1 );
	gSizer21->Add( m_staticText18112111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_azim_min = new wxTextCtrl( m_wizPage8, ID_TEXT_AZIM_MIN, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_azim_min->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_azim_min, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText1811111111 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("deg"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811111111->Wrap( -1 );
	gSizer21->Add( m_staticText1811111111, 0, wxALL, 5 );
	
	m_staticText18112121 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("Endpunkt A2"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18112121->Wrap( -1 );
	gSizer21->Add( m_staticText18112121, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_azim_max = new wxTextCtrl( m_wizPage8, ID_TEXT_AZIM_MAX, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_azim_max->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_azim_max, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText1811111211 = new wxStaticText( m_wizPage8, wxID_ANY, wxT("deg"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811111211->Wrap( -1 );
	gSizer21->Add( m_staticText1811111211, 0, wxALL, 5 );
	
	
	bSizer75->Add( gSizer21, 0, wxEXPAND, 5 );
	
	
	bSizer75->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1031->Add( bSizer75, 0, wxEXPAND, 5 );
	
	
	bSizer1031->Add( 0, 5, 0, wxEXPAND, 5 );
	
	m_bitmap21 = new wxStaticBitmap( m_wizPage8, wxID_ANY, wxBitmap( wxT("Circle.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1031->Add( m_bitmap21, 0, wxALL, 5 );
	
	
	bSizer901->Add( bSizer1031, 0, wxEXPAND, 5 );
	
	
	m_wizPage8->SetSizer( bSizer901 );
	m_wizPage8->Layout();
	bSizer901->Fit( m_wizPage8 );
	wxWizardPageSimple* m_wizPage81 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage81 );
	
	wxBoxSizer* bSizer9011;
	bSizer9011 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer6011111;
	bSizer6011111 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText61121111 = new wxStaticText( m_wizPage81, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText61121111->Wrap( -1 );
	bSizer6011111->Add( m_staticText61121111, 0, wxALL, 5 );
	
	m_staticText6111111111 = new wxStaticText( m_wizPage81, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6111111111->Wrap( -1 );
	m_staticText6111111111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText6111111111->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer6011111->Add( m_staticText6111111111, 0, wxALL, 5 );
	
	m_staticText611121111 = new wxStaticText( m_wizPage81, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText611121111->Wrap( -1 );
	bSizer6011111->Add( m_staticText611121111, 0, wxALL, 5 );
	
	
	bSizer9011->Add( bSizer6011111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6011;
	bSizer6011 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText61121 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Erfassungsbereich"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText61121->Wrap( -1 );
	bSizer6011->Add( m_staticText61121, 0, wxALL, 5 );
	
	m_staticText611121 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Röntgenparameter"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText611121->Wrap( -1 );
	m_staticText611121->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer6011->Add( m_staticText611121, 0, wxALL, 5 );
	
	m_staticText6111111 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Einschalten"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText6111111->Wrap( -1 );
	bSizer6011->Add( m_staticText6111111, 0, wxALL, 5 );
	
	
	bSizer9011->Add( bSizer6011, 0, wxEXPAND, 5 );
	
	m_staticline511 = new wxStaticLine( m_wizPage81, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer9011->Add( m_staticline511, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer9011->Add( 15, 0, 0, wxEXPAND, 5 );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 4, 0, 0 );
	
	m_staticText622 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Hochspannung"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText622->Wrap( -1 );
	gSizer7->Add( m_staticText622, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	spin_voltage = new wxSpinButton( m_wizPage81, ID_SPIN_VOLTAGE, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer7->Add( spin_voltage, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_voltage = new wxStaticText( m_wizPage81, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_voltage->Wrap( -1 );
	staticText_label_voltage->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( staticText_label_voltage, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText371 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("kV"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText371->Wrap( -1 );
	m_staticText371->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( m_staticText371, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6211 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Röhrenstrom"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText6211->Wrap( -1 );
	gSizer7->Add( m_staticText6211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	spin_current = new wxSpinButton( m_wizPage81, ID_SPIN_CURRENT, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer7->Add( spin_current, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_current = new wxStaticText( m_wizPage81, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_current->Wrap( -1 );
	staticText_label_current->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( staticText_label_current, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText37 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("mA"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	m_staticText37->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1811 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("Belichtungszeit"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText1811->Wrap( -1 );
	gSizer7->Add( m_staticText1811, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	textCtrl_exposure = new wxTextCtrl( m_wizPage81, ID_TEXT_EXPOSURE, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_exposure->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( textCtrl_exposure, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText18111 = new wxStaticText( m_wizPage81, wxID_ANY, wxT("(s)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18111->Wrap( -1 );
	gSizer7->Add( m_staticText18111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9011->Add( gSizer7, 0, 0, 5 );
	
	
	m_wizPage81->SetSizer( bSizer9011 );
	m_wizPage81->Layout();
	bSizer9011->Fit( m_wizPage81 );
	wxWizardPageSimple* m_wizPage811 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage811 );
	
	m_wizPage811->SetForegroundColour( wxColour( 0, 0, 0 ) );
	
	wxBoxSizer* bSizer90111;
	bSizer90111 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer601111;
	bSizer601111 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText6112111 = new wxStaticText( m_wizPage811, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6112111->Wrap( -1 );
	bSizer601111->Add( m_staticText6112111, 0, wxALL, 5 );
	
	m_staticText61112111 = new wxStaticText( m_wizPage811, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText61112111->Wrap( -1 );
	bSizer601111->Add( m_staticText61112111, 0, wxALL, 5 );
	
	m_staticText611111111 = new wxStaticText( m_wizPage811, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText611111111->Wrap( -1 );
	m_staticText611111111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText611111111->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer601111->Add( m_staticText611111111, 0, wxALL, 5 );
	
	
	bSizer90111->Add( bSizer601111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer60111;
	bSizer60111 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText611211 = new wxStaticText( m_wizPage811, wxID_ANY, wxT("Erfassungsbereich"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText611211->Wrap( -1 );
	bSizer60111->Add( m_staticText611211, 0, wxALL, 5 );
	
	m_staticText6111211 = new wxStaticText( m_wizPage811, wxID_ANY, wxT("Röntgenparameter"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText6111211->Wrap( -1 );
	bSizer60111->Add( m_staticText6111211, 0, wxALL, 5 );
	
	m_staticText61111111 = new wxStaticText( m_wizPage811, wxID_ANY, wxT("Einschalten"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText61111111->Wrap( -1 );
	m_staticText61111111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer60111->Add( m_staticText61111111, 0, wxALL, 5 );
	
	
	bSizer90111->Add( bSizer60111, 0, wxEXPAND, 5 );
	
	m_staticline5111 = new wxStaticLine( m_wizPage811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer90111->Add( m_staticline5111, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer90111->Add( 15, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer981;
	bSizer981 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer981->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString m_radioBox1Choices[] = { wxT("Neue Messung von Anfang beginnen "), wxT("Neue Messung beginnen bei Punkt #"), wxT("Vorhandene Messung an Punkt # fortsetzen") };
	int m_radioBox1NChoices = sizeof( m_radioBox1Choices ) / sizeof( wxString );
	m_radioBox1 = new wxRadioBox( m_wizPage811, wxID_ANY, wxT("Modus"), wxDefaultPosition, wxDefaultSize, m_radioBox1NChoices, m_radioBox1Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox1->SetSelection( 0 );
	m_radioBox1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_radioBox1->Hide();
	
	bSizer89->Add( m_radioBox1, 1, wxALL, 5 );
	
	
	bSizer981->Add( bSizer89, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer88->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_panel25 = new wxPanel( m_wizPage811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel25->Hide();
	
	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText140 = new wxStaticText( m_panel25, wxID_ANY, wxT("Punkt #"), wxDefaultPosition, wxSize( 60,-1 ), 0 );
	m_staticText140->Wrap( -1 );
	bSizer92->Add( m_staticText140, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	textC_pointnumber = new wxTextCtrl( m_panel25, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer92->Add( textC_pointnumber, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer92->Add( 0, 0, 1, wxEXPAND, 5 );
	
	button_set_point_number = new wxButton( m_panel25, wxID_ANY, wxT("Punkt setzen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer92->Add( button_set_point_number, 0, wxALL, 5 );
	
	
	m_panel25->SetSizer( bSizer92 );
	m_panel25->Layout();
	bSizer92->Fit( m_panel25 );
	bSizer88->Add( m_panel25, 0, wxEXPAND | wxALL, 0 );
	
	m_panel26 = new wxPanel( m_wizPage811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel26->Hide();
	
	wxBoxSizer* bSizer921;
	bSizer921 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText141 = new wxStaticText( m_panel26, wxID_ANY, wxT("Messfile"), wxDefaultPosition, wxSize( 60,-1 ), 0 );
	m_staticText141->Wrap( -1 );
	bSizer921->Add( m_staticText141, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_filePicker1 = new wxFilePickerCtrl( m_panel26, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer921->Add( m_filePicker1, 1, wxALL, 5 );
	
	
	m_panel26->SetSizer( bSizer921 );
	m_panel26->Layout();
	bSizer921->Fit( m_panel26 );
	bSizer88->Add( m_panel26, 0, wxEXPAND | wxALL, 0 );
	
	
	bSizer88->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer981->Add( bSizer88, 1, wxEXPAND, 5 );
	
	
	bSizer981->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticline14 = new wxStaticLine( m_wizPage811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer981->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText5311 = new wxStaticText( m_wizPage811, wxID_ANY, wxT("WARNUNG"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText5311->Wrap( -1 );
	m_staticText5311->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer981->Add( m_staticText5311, 0, wxALL, 5 );
	
	m_staticline15 = new wxStaticLine( m_wizPage811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer981->Add( m_staticline15, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText532 = new wxStaticText( m_wizPage811, wxID_ANY, wxT("Fortsetzen startet eine neue Messung. \nNicht gespeicherte Messdaten und Berechnungen gehen dabei verloren."), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText532->Wrap( -1 );
	m_staticText532->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer981->Add( m_staticText532, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer981->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer90111->Add( bSizer981, 1, wxEXPAND, 5 );
	
	
	m_wizPage811->SetSizer( bSizer90111 );
	m_wizPage811->Layout();
	bSizer90111->Fit( m_wizPage811 );
	
	this->Centre( wxBOTH );
	
	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}
	
	// Connect Events
	spin_detectorrows->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_detectorrows_up ), NULL, this );
	spin_angles->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_angles_down ), NULL, this );
	spin_angles->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_angles_up ), NULL, this );
	textCtrl_trans_min->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_trans_min_changed ), NULL, this );
	textCtrl_trans_max->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_trans_max_changed ), NULL, this );
	textCtrl_azim_min->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_azim_min_changed ), NULL, this );
	textCtrl_azim_max->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_azim_max_changed ), NULL, this );
	spin_voltage->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_voltage_down ), NULL, this );
	spin_voltage->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_voltage_up ), NULL, this );
	spin_current->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_current_down ), NULL, this );
	spin_current->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_current_up ), NULL, this );
	textCtrl_exposure->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_exposure_changed ), NULL, this );
	m_radioBox1->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MeasurementWizard::on_m_radioBox1_clicked ), NULL, this );
	button_set_point_number->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MeasurementWizard::on_button_set_point_number_pressed ), NULL, this );
}

MeasurementWizard::~MeasurementWizard()
{
	// Disconnect Events
	spin_detectorrows->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_detectorrows_up ), NULL, this );
	spin_angles->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_angles_down ), NULL, this );
	spin_angles->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_angles_up ), NULL, this );
	textCtrl_trans_min->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_trans_min_changed ), NULL, this );
	textCtrl_trans_max->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_trans_max_changed ), NULL, this );
	textCtrl_azim_min->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_azim_min_changed ), NULL, this );
	textCtrl_azim_max->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_azim_max_changed ), NULL, this );
	spin_voltage->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_voltage_down ), NULL, this );
	spin_voltage->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_voltage_up ), NULL, this );
	spin_current->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard::on_spin_current_down ), NULL, this );
	spin_current->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard::on_spin_current_up ), NULL, this );
	textCtrl_exposure->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard::on_textCtrl_exposure_changed ), NULL, this );
	m_radioBox1->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MeasurementWizard::on_m_radioBox1_clicked ), NULL, this );
	button_set_point_number->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MeasurementWizard::on_button_set_point_number_pressed ), NULL, this );
	
	m_pages.Clear();
}

MeasurementWizard2::MeasurementWizard2( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style ) 
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxWizardPageSimple* m_wizPage10 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage10 );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer621;
	bSizer621 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText791 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("\nErfassungsbereich\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText791->Wrap( -1 );
	m_staticText791->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_staticText791->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer621->Add( m_staticText791, 1, wxALL, 0 );
	
	m_staticText801 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("\nRöntgenparameter\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText801->Wrap( -1 );
	m_staticText801->SetBackgroundColour( wxColour( 224, 224, 224 ) );
	
	bSizer621->Add( m_staticText801, 1, wxALL, 0 );
	
	m_staticText811 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("\nEinschalten\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText811->Wrap( -1 );
	m_staticText811->SetBackgroundColour( wxColour( 224, 224, 224 ) );
	
	bSizer621->Add( m_staticText811, 1, wxALL, 0 );
	
	
	bSizer82->Add( bSizer621, 0, wxEXPAND, 5 );
	
	m_staticline9 = new wxStaticLine( m_wizPage10, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer82->Add( m_staticline9, 0, wxEXPAND | wxALL, 0 );
	
	
	bSizer82->Add( 0, 20, 0, wxEXPAND, 5 );
	
	wxGridSizer* gSizer21;
	gSizer21 = new wxGridSizer( 0, 4, 0, 0 );
	
	m_staticText623 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Detektorzeilen"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText623->Wrap( -1 );
	gSizer21->Add( m_staticText623, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_detectorrows = new wxSpinButton( m_wizPage10, ID_SPIN_DETECTORROWS, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer21->Add( spin_detectorrows, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_detectorrows = new wxStaticText( m_wizPage10, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_detectorrows->Wrap( -1 );
	staticText_label_detectorrows->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_detectorrows, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_label_detectorrows1 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_detectorrows1->Wrap( -1 );
	staticText_label_detectorrows1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_detectorrows1, 0, wxALL, 5 );
	
	m_staticText6212 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Aufnahmewinkel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6212->Wrap( -1 );
	gSizer21->Add( m_staticText6212, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_angles = new wxSpinButton( m_wizPage10, ID_SPIN_ANGLES, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer21->Add( spin_angles, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_angles = new wxStaticText( m_wizPage10, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_angles->Wrap( -1 );
	staticText_label_angles->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_angles, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	staticText_label_angles1 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_angles1->Wrap( -1 );
	staticText_label_angles1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( staticText_label_angles1, 0, wxALL, 5 );
	
	m_staticText181122 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Startpunkt T1"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181122->Wrap( -1 );
	gSizer21->Add( m_staticText181122, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_trans_min = new wxTextCtrl( m_wizPage10, ID_TEXT_TRANS_MIN, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_trans_min->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_trans_min, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText1811112 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811112->Wrap( -1 );
	gSizer21->Add( m_staticText1811112, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText18111121 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("mm"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18111121->Wrap( -1 );
	gSizer21->Add( m_staticText18111121, 0, wxALL, 5 );
	
	m_staticText1811213 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Endpunkt T2"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811213->Wrap( -1 );
	gSizer21->Add( m_staticText1811213, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_trans_max = new wxTextCtrl( m_wizPage10, ID_TEXT_TRANS_MAX, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_trans_max->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_trans_max, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText18111113 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18111113->Wrap( -1 );
	gSizer21->Add( m_staticText18111113, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText181111131 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("mm"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181111131->Wrap( -1 );
	gSizer21->Add( m_staticText181111131, 0, wxALL, 5 );
	
	m_staticText18112111 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Startpunkt A1"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18112111->Wrap( -1 );
	gSizer21->Add( m_staticText18112111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_azim_min = new wxTextCtrl( m_wizPage10, ID_TEXT_AZIM_MIN, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_azim_min->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_azim_min, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText181111111 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181111111->Wrap( -1 );
	gSizer21->Add( m_staticText181111111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1811111111 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("deg"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811111111->Wrap( -1 );
	gSizer21->Add( m_staticText1811111111, 0, wxALL, 5 );
	
	m_staticText18112121 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("Endpunkt A2"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18112121->Wrap( -1 );
	gSizer21->Add( m_staticText18112121, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	textCtrl_azim_max = new wxTextCtrl( m_wizPage10, ID_TEXT_AZIM_MAX, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_azim_max->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer21->Add( textCtrl_azim_max, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText181111121 = new wxStaticText( m_wizPage10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181111121->Wrap( -1 );
	gSizer21->Add( m_staticText181111121, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1811111211 = new wxStaticText( m_wizPage10, wxID_ANY, wxT("deg"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1811111211->Wrap( -1 );
	gSizer21->Add( m_staticText1811111211, 0, wxALL, 5 );
	
	
	bSizer82->Add( gSizer21, 0, wxEXPAND, 5 );
	
	
	bSizer82->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bitmap21 = new wxStaticBitmap( m_wizPage10, wxID_ANY, wxBitmap( wxT("Circle.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer82->Add( m_bitmap21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_wizPage10->SetSizer( bSizer82 );
	m_wizPage10->Layout();
	bSizer82->Fit( m_wizPage10 );
	wxWizardPageSimple* m_wizPage101 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage101 );
	
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6211;
	bSizer6211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8011 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("\nErfassungsbereich\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText8011->Wrap( -1 );
	m_staticText8011->SetBackgroundColour( wxColour( 224, 224, 224 ) );
	
	bSizer6211->Add( m_staticText8011, 1, wxALL, 0 );
	
	m_staticText7911 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("\nRöntgenparameter\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText7911->Wrap( -1 );
	m_staticText7911->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_staticText7911->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer6211->Add( m_staticText7911, 1, wxALL, 0 );
	
	m_staticText8111 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("\nEinschalten\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText8111->Wrap( -1 );
	m_staticText8111->SetBackgroundColour( wxColour( 224, 224, 224 ) );
	
	bSizer6211->Add( m_staticText8111, 1, wxALL, 0 );
	
	
	bSizer84->Add( bSizer6211, 0, wxEXPAND, 5 );
	
	m_staticline91 = new wxStaticLine( m_wizPage101, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer84->Add( m_staticline91, 0, wxEXPAND | wxALL, 0 );
	
	
	bSizer84->Add( 0, 20, 0, wxEXPAND, 5 );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 4, 0, 0 );
	
	m_staticText622 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("Hochspannung"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText622->Wrap( -1 );
	gSizer7->Add( m_staticText622, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	spin_voltage = new wxSpinButton( m_wizPage101, ID_SPIN_VOLTAGE, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer7->Add( spin_voltage, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_voltage = new wxStaticText( m_wizPage101, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_voltage->Wrap( -1 );
	staticText_label_voltage->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( staticText_label_voltage, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText371 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("kV"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText371->Wrap( -1 );
	m_staticText371->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( m_staticText371, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6211 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("Röhrenstrom"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText6211->Wrap( -1 );
	gSizer7->Add( m_staticText6211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	spin_current = new wxSpinButton( m_wizPage101, ID_SPIN_CURRENT, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer7->Add( spin_current, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_current = new wxStaticText( m_wizPage101, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_current->Wrap( -1 );
	staticText_label_current->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( staticText_label_current, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText37 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("mA"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	m_staticText37->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1811 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("Belichtungszeit"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText1811->Wrap( -1 );
	gSizer7->Add( m_staticText1811, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	textCtrl_exposure = new wxTextCtrl( m_wizPage101, ID_TEXT_EXPOSURE, wxT("N/A"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	textCtrl_exposure->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	gSizer7->Add( textCtrl_exposure, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	m_staticText18111 = new wxStaticText( m_wizPage101, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18111->Wrap( -1 );
	gSizer7->Add( m_staticText18111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText181111 = new wxStaticText( m_wizPage101, wxID_ANY, wxT("sec"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText181111->Wrap( -1 );
	gSizer7->Add( m_staticText181111, 0, wxALL, 5 );
	
	
	bSizer84->Add( gSizer7, 0, wxEXPAND, 5 );
	
	
	bSizer84->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_wizPage101->SetSizer( bSizer84 );
	m_wizPage101->Layout();
	bSizer84->Fit( m_wizPage101 );
	wxWizardPageSimple* m_wizPage102 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage102 );
	
	wxBoxSizer* bSizer79;
	bSizer79 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6212;
	bSizer6212 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8012 = new wxStaticText( m_wizPage102, wxID_ANY, wxT("\nErfassungsbereich\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText8012->Wrap( -1 );
	m_staticText8012->SetBackgroundColour( wxColour( 208, 208, 208 ) );
	
	bSizer6212->Add( m_staticText8012, 1, wxALL, 0 );
	
	m_staticText8112 = new wxStaticText( m_wizPage102, wxID_ANY, wxT("\nRöntgenparameter\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText8112->Wrap( -1 );
	m_staticText8112->SetBackgroundColour( wxColour( 208, 208, 208 ) );
	
	bSizer6212->Add( m_staticText8112, 1, wxALL, 0 );
	
	m_staticText7912 = new wxStaticText( m_wizPage102, wxID_ANY, wxT("\nEinschalten\n"), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTRE );
	m_staticText7912->Wrap( -1 );
	m_staticText7912->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_staticText7912->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer6212->Add( m_staticText7912, 1, wxALL, 0 );
	
	
	bSizer79->Add( bSizer6212, 0, wxEXPAND, 5 );
	
	m_staticline92 = new wxStaticLine( m_wizPage102, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer79->Add( m_staticline92, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer981;
	bSizer981 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer981->Add( 0, 20, 0, wxEXPAND, 5 );
	
	m_staticText5311 = new wxStaticText( m_wizPage102, wxID_ANY, wxT("WARNUNG"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText5311->Wrap( -1 );
	m_staticText5311->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer981->Add( m_staticText5311, 0, wxALL, 5 );
	
	m_staticText532 = new wxStaticText( m_wizPage102, wxID_ANY, wxT("Fortsetzen startet eine neue Messung. \nNicht gespeicherte Messdaten gehen dabei verloren."), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText532->Wrap( -1 );
	m_staticText532->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer981->Add( m_staticText532, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer981->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer79->Add( bSizer981, 1, wxEXPAND, 5 );
	
	
	m_wizPage102->SetSizer( bSizer79 );
	m_wizPage102->Layout();
	bSizer79->Fit( m_wizPage102 );
	
	this->Centre( wxBOTH );
	
	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}
	
	// Connect Events
	spin_detectorrows->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_detectorrows_up ), NULL, this );
	spin_angles->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_angles_down ), NULL, this );
	spin_angles->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_angles_up ), NULL, this );
	textCtrl_trans_min->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_trans_min_changed ), NULL, this );
	textCtrl_trans_max->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_trans_max_changed ), NULL, this );
	textCtrl_azim_min->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_azim_min_changed ), NULL, this );
	textCtrl_azim_max->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_azim_max_changed ), NULL, this );
	spin_voltage->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_voltage_down ), NULL, this );
	spin_voltage->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_voltage_up ), NULL, this );
	spin_current->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_current_down ), NULL, this );
	spin_current->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_current_up ), NULL, this );
	textCtrl_exposure->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_exposure_changed ), NULL, this );
}

MeasurementWizard2::~MeasurementWizard2()
{
	// Disconnect Events
	spin_detectorrows->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_detectorrows_up ), NULL, this );
	spin_angles->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_angles_down ), NULL, this );
	spin_angles->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_angles_up ), NULL, this );
	textCtrl_trans_min->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_trans_min_changed ), NULL, this );
	textCtrl_trans_max->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_trans_max_changed ), NULL, this );
	textCtrl_azim_min->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_azim_min_changed ), NULL, this );
	textCtrl_azim_max->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_azim_max_changed ), NULL, this );
	spin_voltage->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_voltage_down ), NULL, this );
	spin_voltage->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_voltage_up ), NULL, this );
	spin_current->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MeasurementWizard2::on_spin_current_down ), NULL, this );
	spin_current->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MeasurementWizard2::on_spin_current_up ), NULL, this );
	textCtrl_exposure->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MeasurementWizard2::on_textCtrl_exposure_changed ), NULL, this );
	
	m_pages.Clear();
}

ComputationWizard::ComputationWizard( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style ) 
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxWizardPageSimple* m_wizPage5 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage5 );
	
	wxBoxSizer* bSizer9012;
	bSizer9012 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer601111;
	bSizer601111 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText611111111 = new wxStaticText( m_wizPage5, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText611111111->Wrap( -1 );
	m_staticText611111111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText611111111->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer601111->Add( m_staticText611111111, 0, wxALL, 5 );
	
	m_staticText6112111 = new wxStaticText( m_wizPage5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6112111->Wrap( -1 );
	bSizer601111->Add( m_staticText6112111, 0, wxALL, 5 );
	
	m_staticText61112111 = new wxStaticText( m_wizPage5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText61112111->Wrap( -1 );
	bSizer601111->Add( m_staticText61112111, 0, wxALL, 5 );
	
	
	bSizer9012->Add( bSizer601111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6012;
	bSizer6012 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText61122 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("Neue Tomographie"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_staticText61122->Wrap( -1 );
	m_staticText61122->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer6012->Add( m_staticText61122, 0, wxALL, 5 );
	
	
	bSizer9012->Add( bSizer6012, 0, wxEXPAND, 5 );
	
	m_staticline512 = new wxStaticLine( m_wizPage5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer9012->Add( m_staticline512, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer9012->Add( 15, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10311;
	bSizer10311 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText103 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("Für die Berechnung des Sinogramms sind Informationen über die gewünschte \nBildgröße nötig. Durch Fortsetzen kann eine Quelldatei ausgewählt werden.\n"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText103->Wrap( -1 );
	bSizer10311->Add( m_staticText103, 0, wxALL, 2 );
	
	
	bSizer10311->Add( 0, 35, 0, wxEXPAND, 5 );
	
	wxGridSizer* gSizer211;
	gSizer211 = new wxGridSizer( 0, 3, 0, 0 );
	
	m_staticText6231 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("Detektorzeilen"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText6231->Wrap( -1 );
	gSizer211->Add( m_staticText6231, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_detectorrows1 = new wxSpinButton( m_wizPage5, ID_SPIN_DETECTORROWS, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer211->Add( spin_detectorrows1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_detectorrows1 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_detectorrows1->Wrap( -1 );
	staticText_label_detectorrows1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer211->Add( staticText_label_detectorrows1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText62121 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("Aufnahmewinkel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText62121->Wrap( -1 );
	gSizer211->Add( m_staticText62121, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	spin_angles1 = new wxSpinButton( m_wizPage5, ID_SPIN_ANGLES, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_HORIZONTAL );
	gSizer211->Add( spin_angles1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );
	
	staticText_label_angles1 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("N/A"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	staticText_label_angles1->Wrap( -1 );
	staticText_label_angles1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	gSizer211->Add( staticText_label_angles1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer10311->Add( gSizer211, 0, wxEXPAND, 5 );
	
	
	bSizer10311->Add( 0, 35, 0, wxEXPAND, 5 );
	
	m_staticline16 = new wxStaticLine( m_wizPage5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10311->Add( m_staticline16, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer9811;
	bSizer9811 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText53111 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("WARNUNG"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText53111->Wrap( -1 );
	m_staticText53111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer9811->Add( m_staticText53111, 0, wxALL, 5 );
	
	m_staticline17 = new wxStaticLine( m_wizPage5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer9811->Add( m_staticline17, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText5321 = new wxStaticText( m_wizPage5, wxID_ANY, wxT("Fortsetzen startet eine neue Berechnung.\nNicht gespeicherte Messdaten oder vorausgegangene Berechnungen gehen \ndabei verloren."), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText5321->Wrap( -1 );
	m_staticText5321->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9811->Add( m_staticText5321, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer10311->Add( bSizer9811, 1, wxEXPAND, 5 );
	
	
	bSizer10311->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer9012->Add( bSizer10311, 1, wxEXPAND, 5 );
	
	
	m_wizPage5->SetSizer( bSizer9012 );
	m_wizPage5->Layout();
	bSizer9012->Fit( m_wizPage5 );
	
	this->Centre( wxBOTH );
	
	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}
	
	// Connect Events
	spin_detectorrows1->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( ComputationWizard::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows1->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( ComputationWizard::on_spin_detectorrows_up ), NULL, this );
	spin_angles1->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( ComputationWizard::on_spin_angles_down ), NULL, this );
	spin_angles1->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( ComputationWizard::on_spin_angles_up ), NULL, this );
}

ComputationWizard::~ComputationWizard()
{
	// Disconnect Events
	spin_detectorrows1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( ComputationWizard::on_spin_detectorrows_down ), NULL, this );
	spin_detectorrows1->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( ComputationWizard::on_spin_detectorrows_up ), NULL, this );
	spin_angles1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( ComputationWizard::on_spin_angles_down ), NULL, this );
	spin_angles1->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( ComputationWizard::on_spin_angles_up ), NULL, this );
	
	m_pages.Clear();
}
