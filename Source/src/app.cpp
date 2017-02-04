const int BUILD = 172201;

#include "app.h"

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include "wx_frames.h"
#include "tomography.h"
#include "measurement.h"
#include "device_phywe09058_99.h"
#include "device_arduino.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// using windres on windows and objcopy for elf binaries to convert any file type to an object file
// and link to my binary
// Windows: Application icon is set using a resource.rc file and proving a *.ico file
// Using windres (MinGW) the resource.rc file is converted to resource.coff and linked

// ============================================================================
// implementation
// ============================================================================

IMPLEMENT_APP(SimpleCTApp)

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool SimpleCTApp::OnInit()
{

	if ( !wxApp::OnInit() )
		return false;

	bool AllDevicesOK = true;

	try{
		// Initialize measurement and tomography objects
		boost::shared_ptr<Tomography> pMyTomography( new Tomography( 128, 128 ) );
		boost::shared_ptr<Measurement> pMyMeasurement( new Measurement(pMyTomography) );

		// Create the application windows
		wxImage::AddHandler(new wxPNGHandler);
		pMainWindow = new CustomMainFrame(
				NULL,
				wxID_ANY,
				wxString::Format("SimpleCT Build %d", BUILD),
				pMyTomography,
				pMyMeasurement);
		pMainWindow->Show(true);
		pConsoleWindow = new wxLogWindow( pMainWindow, "Debug-Log", false);

		try{
			pMyMeasurement->init_device_xraydev( xrayd::com_port_xraydev );
		}
		catch(...){
			AllDevicesOK = false;
		}
		try{
			pMyMeasurement->init_device_arduino( arduino::com_port_arduino );
		}
		catch(...){
			AllDevicesOK = false;

		}
	}
	catch( boost::system::system_error &err ){
		wxMessageBox( err.what(), "Kritischer Programmfehler", wxICON_ERROR );
		return false;
	}
	catch( std::runtime_error &err ){
		wxMessageBox( err.what(), "Kritischer Programmfehler", wxICON_ERROR );
		return false;
	}

	return true;
}

int SimpleCTApp::OnRun(){

	// Log console message
	wxString Message(
			wxString::Format(" ### SimpleCT Version %d gestartet ###", BUILD));
	if (pConsoleWindow != NULL)
		wxLogMessage(Message);

	return wxApp::OnRun();
}
