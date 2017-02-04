#define DEFAULT_NEXT_MESSAGE_DELAY 10 // 200
#define DEFAULT_SERIAL_READ_TIMEOUT 1000 // 2000
#define DEFAULT_SERIAL_WRITE_TIMEOUT 25
#define DEFAULT_SERVICE_RESTART_DELAY 15

#include "device_phywe09058_99.h"

#include <stdexcept>

#include <boost/format.hpp>

#include <wx/thread.h> // for wxThread::Sleep()
#include <wx/msgdlg.h>

std::string xrayd::com_port_xraydev("\\\\.\\COM13");

// Purpose: Class constructor
// Return:	n/a
// Error:	Throws exception of type boost::system::system_error in case of error
PHYWE09058_99::PHYWE09058_99( )
:	_HVSTAT_ON(false), _CMOD_BUSY(false), _KMOD_CLOSE(true), _MODE_REMOTE(false),
	_HV(0.0), _CURR(0.0), _TPOS(0.0), _CPOS(0.0), _CRT(0), _VERSION(""), _ANOD(""),
	SerialDevice( DEFAULT_SERVICE_RESTART_DELAY, DEFAULT_SERIAL_READ_TIMEOUT,
			DEFAULT_SERIAL_WRITE_TIMEOUT, DEFAULT_NEXT_MESSAGE_DELAY) {}

// Purpose: Class destructor
// Return:	n/a
// Error:	Throws no exceptions
PHYWE09058_99::~PHYWE09058_99() {

	try {
		this->TurnOff();
	} catch (...) {
		// No exceptions from the destructor...
	}
}

// Purpose: Establish connection to x-ray device and test for proper configuration
// Return:	void
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
void PHYWE09058_99::Init( std::string port ) {

	unsigned int baudrate = 9600;
	OpenPort(port, baudrate);

	this->MODE_REMOTE(true);

	std::string FullVersionRef("PHYWE x-ray-unit 09058.99-1 Ver 02.00/8.1.02");

	// We generate a substring, which only contains the type number and description
	// By doing so, this still works if the firmware changes
	size_t len = std::string( "PHYWE x-ray-unit 09058.99-1" ).length();
	std::string VersionRef = FullVersionRef.substr( 0, len );

	// 3 attempts to get VERSION from x-ray-device
	int attempt = 1;
	while( get_VERSION().substr(0, len).compare(VersionRef) ){
		wxThread::Sleep(15);
		if( attempt++ == 3 ) throw std::runtime_error("Geräteversion des "
				"Röntgengeräts konnte nicht ermittelt werden.");
	}

	this->get_ANOD();
	this->get_STAT();
	this->KMOD_OPEN(true);
}

// Purpose: Set the device parameters and turn x-rays ON from outside the class
// Return:	void
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
void PHYWE09058_99::TurnOn( double VoltageToSet, double CurrentToSet ) {

	this->set(xrayd::HighVoltage, VoltageToSet);
	this->set(xrayd::Current, CurrentToSet);
	this->set(xrayd::HVStatus, xrayd::On);
}

// Purpose: Turn x-rays OFF from outside the class
// Return:	void
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
void PHYWE09058_99::TurnOff() {

	this->set(xrayd::HVStatus, xrayd::Off);
}

// Purpose: Internal wrapper to set properties of type BOOL
// Return:	void
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
void PHYWE09058_99::set( xrayd::enumInts Property, bool Value ) {


	int p = Property;
	switch (p) {
	case xrayd::HVStatus:
		if ( this->HVSTAT(Value)!= Value)
			throw std::runtime_error("Fehler bei Übermittlung von HVSTAT-Parameter.");
		break;
	case xrayd::CModBusy:
		if (this->CMOD_BUSY(Value) != Value)
			throw std::runtime_error("Fehler bei Übermittlung von CMOD-Parameter.");
		break;
	case xrayd::KModBusy:
		this->KMOD_OPEN(Value);
		break;
	case xrayd::ModeRemote:
		this->MODE_REMOTE(Value);
		break;
	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät "
						"kann nicht eingestellt werden.");
	}
}

// Purpose: Internal wrapper to set properties of type DOUBLE
// Return:	void
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
void PHYWE09058_99::set( xrayd::enumDoubles Property, double Value ) {
// Purpose: Public setter for device properties of type DOUBLE

	int p = Property;
	switch (p) {
	case xrayd::HighVoltage:{
		// Convert to string, to avoid comparing doubles
		std::string res = boost::str(boost::format("%.1f") % this->HV(Value));
		std::string val = boost::str(boost::format("%.1f") % Value);
		if ( res.compare(val) )
			throw std::runtime_error("Fehler bei Übermittlung der Röhrenspannung.");
		break;
	}

	case xrayd::Current:{
		// Convert to string, to avoid comparing doubles
		std::string res = boost::str(boost::format("%.2f") % this->CURR(Value));
		std::string val = boost::str(boost::format("%.2f") % Value);
		if ( res.compare(val) ) {
			throw std::runtime_error("Fehler bei Übermittlung des Röhrenstroms.");
		}
		break;
	}

	case xrayd::TPosition:{
		// Convert to string, to avoid comparing doubles
		std::string res = boost::str(boost::format("%.2f") % this->TPOS(Value));
		std::string val = boost::str(boost::format("%.2f") % Value);
		if ( res.compare(val) )
			throw std::runtime_error("Fehler bei Übermittlung des Zählrohrwinkels.");
		break;
	}

	case xrayd::CPosition:{
		// Convert to string, to avoid comparing doubles
		std::string res = boost::str(boost::format("%.2f") % this->CPOS(Value));
		std::string val = boost::str(boost::format("%.2f") % Value);
		if ( res.compare(val) )
			throw std::runtime_error("Fehler bei Übermittlung des Kristallwinkels.");
		break;
	}

	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät "
				"kann nicht eingestellt werden.");
	}
}

// Purpose: Internal wrapper to read properties of type BOOL and INT
// Return:	Type INT value, determined by the value for parameter
//			enumInts Property
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::get( xrayd::enumInts Property ) {

	int p = Property;
	switch (p) {
	case xrayd::HVStatus:
		return this->get_HVSTAT();
	case xrayd::CModBusy:
		return this->get_CMOD_BUSY();
	case xrayd::ModeRemote:
		return true;
	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät "
				"kann nicht abgefragt werden.");
	}
}

int PHYWE09058_99::get( xrayd::enumInts Property, int TINT ) {

	int p = Property;
	switch (p) {
	case xrayd::CountRate:
			return this->get_CRT( TINT ); //
	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät "
				"kann nicht abgefragt werden.");
	}
}


// Purpose: Internal wrapper to read properties of type DOUBLE
// Return:	Type DOUBLE, determined by the value for parameter
//			enumInts Property
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
double PHYWE09058_99::get( xrayd::enumDoubles Property ) {

	int p = Property;
	switch (p) {
	case xrayd::HighVoltage:
		return this->get_HV();
	case xrayd::Current:
		return this->get_CURR();
	case xrayd::TPosition:
		return this->get_TPOS();
	case xrayd::CPosition:
		return this->get_CPOS();
	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät"
				"kann nicht abgefragt werden.");
	}
}

// Purpose: Internal wrapper to read properties of type STRING
// Return:	Type STRING, determined by the value for parameter
//			enumInts Property
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
std::string PHYWE09058_99::get( xrayd::enumStrings Property ) {

	int p = Property;
	switch(p){
	case xrayd::Version :
		return this->get_VERSION();
	case xrayd::AnodeMaterial:
		return this->get_ANOD();
	default:
		throw std::runtime_error("Unbekannter Parameter für Röntgengerät"
				"kann nicht abgefragt werden.");
	}
}

// -------- Serial command implementations --------

// Purpose: Tell x-ray-device to turn high voltage ON/OFF
// Return:	Type INT 0 or 1 (i.e. the read value for HVSTAT
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::HVSTAT(bool arg_HVON) {

	get_HVSTAT();
	switch (arg_HVON) {
	case xrayd::On:
		WriteSerial2("HVSTAT=ON");
		break;
	case xrayd::Off:
		WriteSerial2("HVSTAT=OFF");
		break;
	default:
		throw std::runtime_error("Ungültiger Wert für Parameter HVSTAT "
				"an Röntgengerät.");
	}
	return get_HVSTAT();
}

// Purpose: ??? Needs to be set to busy before measurement
// Return:	Type INT 0 or 1 (i.e. the read value for CMOD
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::CMOD_BUSY(bool arg_CMODBUSY) {

	if (arg_CMODBUSY) WriteSerial2("CMOD=BUSY");
	get_HVSTAT();
	return get_CMOD_BUSY();
}

// Purpose: ???
// Return:	void
// Error:	Throws exception of type boost::system::system_error
//			in case of error
void PHYWE09058_99::KMOD_OPEN(bool arg_KMODOPEN) {

	if (arg_KMODOPEN) WriteSerial2("KMOD=OPEN");
}

// Purpose: Set the device to remote mode, i.e. PC-controlled via RS232
// 			The device can not be reset to manual mode once in remote mode
// Return:	void
// Error:	Throws exception of type boost::system::system_error
//			in case of error
void PHYWE09058_99::MODE_REMOTE(bool arg_MODEREMOTE) {

	if (arg_MODEREMOTE) WriteSerial2("MODE=REMOTE");
}

// Purpose: Tell the device which high voltage to use
//			(must be between 0kV and 35kV)
// Return:	Type DOUBLE (i.e. the read value for HV
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
double PHYWE09058_99::HV(double arg_HV) {

	if (arg_HV < 0 || arg_HV > 35.0)
		throw std::runtime_error("Die Röhrenspannung muss zwischen 0 und 35kV liegen.");

	WriteSerial2(boost::str(boost::format("HV=%.1f") % arg_HV));
	return get_HV();
}

// Purpose: Tell the device which anode current to use
//			(must be between 0.0mA and 1mA)
// Return:	Type DOUBLE (i.e. the read value for CURR
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
double PHYWE09058_99::CURR(double arg_CURR) {

	if (arg_CURR < 0 || arg_CURR > 1.0)
		throw std::runtime_error("Der Röhrenstrom muss zwischen 0 und 1mA liegen.");
	WriteSerial2(boost::str(boost::format("CURR=%.1f") % arg_CURR));
	return get_CURR();
}

// Purpose: Set the detector angle (only if goniometer is connected)
// Return:	Type DOUBLE (i.e. the read value for TPOS
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
double PHYWE09058_99::TPOS(double arg_TPOS) {

	if (arg_TPOS < 0 || arg_TPOS > 50) // TODO, arbitrary
		throw std::runtime_error("Ungültiger Wert für Parameter TPOS an Röntgengerät.");
	WriteSerial2(boost::str(boost::format("TPOS=%.1f") % arg_TPOS));
	return get_TPOS();
}

// Purpose: Set the crystal angle (only if goniometer is connected)
// Return:	Type DOUBLE (i.e. the read value for CPOS
//			after the command was written)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
double PHYWE09058_99::CPOS(double arg_CPOS) {

	if (arg_CPOS < 0 || arg_CPOS > 360)
		throw std::runtime_error("Ungültiger Wert für Parameter TPOS an Röntgengerät.");
	WriteSerial2(boost::str(boost::format("CPOS=%.1f") % arg_CPOS));
	return get_CPOS();
}

// Purpose: ??? Set to 2 before measurement
// Return:	void
// Error:	Throws exception of type boost::system::system_error
//			in case of error
void PHYWE09058_99::TINT(int arg_TINT) {

	WriteSerial2(boost::str(boost::format("TINT=%i") % arg_TINT));
}

// Purpose: Check if xrays are ON or OFF
// Return:	Type INT 0 or 1 (i.e OFF or ON)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::get_HVSTAT() {

	wxThread::Sleep( _times.NEXT_MESSAGE_DELAY);
	WriteSerial2("HVSTAT?");

	std::string val = this->ReadSerial2();

	if (!val.compare("ON"))
		return 1;
	if (!val.compare("OFF"))
		return 0;
	else
		throw std::runtime_error("Fehlerhafter Wert für Parameter HVSTAT an Röntgenröhre gelesen.");
}

// Purpose: Check CMOD
// Return:	Type INT 0 or 1 (i.e READY or BUSY)
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::get_CMOD_BUSY() {
// Purpose: Get the high voltage state, i.e. On or Off

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	this->WriteSerial2("CMOD?");

	std::string val = this->ReadSerial2();

	if (!val.compare("BUSY"))
		return 1;
	if (!val.compare("READY"))
		return 0;
	else
		throw std::runtime_error("Fehlerhafter Wert für Parameter CMOD "
				"an Röntgenröhre gelesen.");
}

// Purpose: Get the set high voltage
// Return:	Type DOUBLE (should be between 0.0 and 35.0kV)
// Error:	Throws exception of type boost::system::system_error
//			in case of error
double PHYWE09058_99::get_HV() {

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("HV?");

	std::string Number = this->ReadSerial2();
	double val = atof(Number.c_str());
	return (roundf(10 * val) / 10);
}

// Purpose: Get the set current
// Return:	Type DOUBLE (should be between 00.0 and 01.0mA)
// Error:	Throws exception of type boost::system::system_error
//			in case of error
double PHYWE09058_99::get_CURR() {

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("CURR?");

	std::string Number = this->ReadSerial2();
	double val = atof(Number.c_str());
	return (roundf(100 * val) / 100);
}

// Purpose: Get the detector angle (only if goniometer is connected)
// Return:	Type DOUBLE
// Error:	Throws exception of type boost::system::system_error
//			in case of error
double PHYWE09058_99::get_TPOS() {

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("TPOS?");

	std::string Number = this->ReadSerial2();
	double val = atof(Number.c_str());
	return val;
}

// Purpose: Get the crystal angle (only if goniometer is connected)
// Return:	Type DOUBLE
// Error:	Throws exception of type boost::system::system_error
//			in case of error
double PHYWE09058_99::get_CPOS() {
	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("CPOS?");

	std::string Number = this->ReadSerial2();
	double val = atof(Number.c_str());
	return val;
}

// Purpose: Get the ! COUNT RATE !
// Return:	Type INT
// Error:	Throws exception of type boost::system::system_error
//			in case of error
int PHYWE09058_99::get_CRT( int TimeIntervall ) {

	TINT( TimeIntervall );

	wxThread::Sleep(10);
	CMOD_BUSY(true);

	int State;
	do {
		State = this->get_CMOD_BUSY();
		wxThread::Sleep(50);
	} while (State != 0 );

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("CRT?");

	std::string Number = this->ReadSerial2();
	int val;
	val = atoi(Number.c_str());
	return val;
}

// Purpose: Get the device version
// Return:	Type STRING
// Error:	Throws exception of type boost::system::system_error
//			in case of error
std::string PHYWE09058_99::get_VERSION() {
// Purpose: Get device version

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("VERSION?");
	wxThread::Sleep(25);
	std::string val = this->ReadSerial2();
	return val;
}

// Purpose: Get installed anode material (e.g Wo or Cu)
// Return:	Type STRING
// Error:	Throws exception of type boost::system::system_error
//			in case of error
std::string PHYWE09058_99::get_ANOD() {

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	WriteSerial2("ANOD?");

	std::string val = this->ReadSerial2();
	return val;
}

// Purpose: Get device status ???
// Return:	Type STRING
// Error:	Throws exception of type std::runtime_error or
//			boost::system::system_error in case of error
int PHYWE09058_99::get_STAT() {

	wxThread::Sleep( this->_times.NEXT_MESSAGE_DELAY);
	this->WriteSerial2("STAT?");

	std::string val = this->ReadSerial2();

	if (!val.compare("BUSY"))
		return 1;
	if (!val.compare("READY"))
		return 0;
	else
		throw std::runtime_error("Fehlerhafter Wert für Parameter "
				"STAT an Röntgenröhre gelesen.");
}
