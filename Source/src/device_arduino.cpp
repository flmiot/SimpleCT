
#define DEFAULT_NEXT_MESSAGE_DELAY 25
#define DEFAULT_SERIAL_READ_TIMEOUT 250
#define DEFAULT_SERIAL_WRITE_TIMEOUT 50
#define DEFAULT_SERVICE_RESTART_DELAY 0

#include "device_arduino.h"

#include <stdexcept>
#include <cmath>

#include <boost/format.hpp>

#include <wx/thread.h> // for wxThread::Sleep()

std::string arduino::com_port_arduino("\\\\.\\COM7");

Arduino::Arduino() :
		_command_led_on("LED=ON"), _command_led_off("LED=OFF"), _command_status(
				"STATUS?"), _command_new_zero("NEW_ZERO"), _command_trans_pos(
				"TPOS="), _command_azimu_pos("APOS="), _command_get_trans_pos(
				"TPOS?"), _command_get_azimu_pos("APOS?"), _command_get_trans_pos_setpoint("TPOS_SET?"),
				_command_get_azimu_pos_setpoint("APOS_SET?"), _command_reset(
				"RESET"), _command_calibrate("CALIB"), _command_version(
				"VERSION?"), _command_sync_package("SYNC"), _pSyncPackage(NULL),
				SerialDevice( DEFAULT_SERVICE_RESTART_DELAY, DEFAULT_SERIAL_READ_TIMEOUT,
						DEFAULT_SERIAL_WRITE_TIMEOUT, DEFAULT_NEXT_MESSAGE_DELAY) {
}

Arduino::~Arduino() {
}

void Arduino::Init( std::string port ) {
// Purpose: Establish connection to arduino

	unsigned int baudrate = 9600;
	OpenPort(port, baudrate);

	if(this->get_status().compare("OK")){
		throw std::runtime_error("Gerät Arduino Leonard ist nicht bereit.");
	}

	_pSyncPackage = new ArduinoSyncPackage();
	this->sync_package(_pSyncPackage);
}

int Arduino::light_led(bool ON) {
	//return (ON) ? WriteSerial(_command_led_on) : WriteSerial(_command_led_off);
	return 1;
}

void Arduino::set_tpos_micrometer( int Value ) {

	if(_pSyncPackage == NULL)
		throw std::runtime_error("Keine gültigen Geometrie-Einstellungen gefunden.");

	int min_um = _pSyncPackage->trans.min_um;
	int max_um = _pSyncPackage->trans.max_um;

	if(Value < min_um || Value > max_um)
		throw std::runtime_error("Ungültiger absoluter Wert für trans. Motorposition.");


	int range_um = max_um - min_um;
	int pos_au = (int)((1.0f * Value -  min_um) / (1.0f * range_um) * _pSyncPackage->trans.steps);

	set_tpos_au(pos_au);
}

// Purpose: Set transverse position (arbitrary units) and check back
void Arduino::set_tpos_au( int Value ) {

	if(_pSyncPackage == NULL)
		throw std::runtime_error("Keine gültigen Geometrie-Einstellungen gefunden.");

	if(Value < 0 || Value > _pSyncPackage->trans.steps)
		throw std::runtime_error("Ungültiger relativer Wert für trans. Motorposition.");

	std::string Command = boost::str(boost::format("TPOS=%i") % Value);
	wxThread::Sleep( _times.NEXT_MESSAGE_DELAY);
	WriteSerial2(Command);

	wxThread::Sleep( _times.NEXT_MESSAGE_DELAY);
	if( get_tpos_setpoint_au( ) != Value)
		throw std::runtime_error("Ungültiger Wert beim Zurücklesen.");
}

void Arduino::set_apos_millidegree( int Value ) {
// Purpose: Set azimuthal position (unit millidregree)
// Return:	0 if successful, 1 otherwise

	if(_pSyncPackage == NULL)
		throw std::runtime_error("Keine gültigen Geometrie-Einstellungen gefunden.");

	int min_mdeg = _pSyncPackage->azimu.min_mdeg; // presumably 0
	int max_mdeg = _pSyncPackage->azimu.max_mdeg; // presumably 360000 or 180000

	if(Value < min_mdeg || Value > max_mdeg)
		throw std::runtime_error("Ungültiger absoluter Wert für azimu. Motorposition.");

	int range_mdeg = max_mdeg - min_mdeg;
	int pos_au = (int)((1.0f * Value -  min_mdeg) / (1.0f * range_mdeg) * _pSyncPackage->azimu.steps);

	set_apos_au(pos_au);

}

void Arduino::set_apos_au( int Value ) {
// Purpose: Set azimuthal position (arbitrary units)

	if(_pSyncPackage == NULL)
		throw std::runtime_error("Keine gültigen Geometrie-Einstellungen gefunden.");

	if(Value < 0 || Value > _pSyncPackage->azimu.steps)
		throw std::runtime_error("Ungültiger relativer Wert für azimu. Motorposition.");

	std::string Command = boost::str(boost::format("APOS=%i") % Value);
	wxThread::Sleep( _times.NEXT_MESSAGE_DELAY);
	WriteSerial2(Command);

	wxThread::Sleep( _times.NEXT_MESSAGE_DELAY);
	if( get_apos_setpoint_au( ) != Value)
		throw std::runtime_error("Ungültiger Wert beim Zurücklesen.");
}

int Arduino::get_tpos_micrometer() {
// Purpose: 	Get transverse position (arbitrary units)
// (!) Return:	TPOS Value, 999 999 999 in case of error, which
//				should be far away from any plausible value

	int error = 999999999;
	if(_pSyncPackage == NULL) return error;

	int pos_au = get_tpos_au();
	if(pos_au < 0 ) return error;

	int min_um = _pSyncPackage->trans.min_um;
	int max_um = _pSyncPackage->trans.max_um;
	int range_um = max_um - min_um;
	return range_um * (1.0f * pos_au) / (1.0f * _pSyncPackage->trans.steps) + min_um;
}

int Arduino::get_tpos_au() {
	WriteSerial2(_command_get_trans_pos);
	std::string Result(this->ReadSerial2());
	return atoi(Result.c_str());
}

int Arduino::get_tpos_setpoint_au() {
	WriteSerial2(_command_get_trans_pos_setpoint);
	std::string Result(this->ReadSerial2());
	return atoi(Result.c_str());
}

int Arduino::get_apos_millidegree() {
// Purpose: 	Get azimuthal position (arbitrary units)
// (!) Return:	APOS Value, 999 999 999 in case of error, which
//				should be far away from any plausible value

	int error = 999999999;
	if(_pSyncPackage == NULL) return error;

	int pos_au = get_apos_au();
	if(pos_au < 0 ) return error;

	int min_mdeg = _pSyncPackage->azimu.min_mdeg;
	int max_mdeg = _pSyncPackage->azimu.max_mdeg;
	int range_mdeg = max_mdeg - min_mdeg;
	return range_mdeg * (1.0f * pos_au) / (1.0f * _pSyncPackage->azimu.steps) + min_mdeg;
}

int Arduino::get_apos_au() {
	WriteSerial2(_command_get_azimu_pos);
	std::string Result(this->ReadSerial2());
	return atoi(Result.c_str());
}

int Arduino::get_apos_setpoint_au() {
	WriteSerial2(_command_get_azimu_pos_setpoint);
	std::string Result(this->ReadSerial2());
	return atoi(Result.c_str());
}

std::string Arduino::get_status() {
	WriteSerial2(_command_status);
	return this->ReadSerial2();
}

std::string Arduino::get_version() {
	WriteSerial2(_command_version);
	return this->ReadSerial2();
}

void Arduino::new_zero() {
	WriteSerial2(_command_new_zero);
}

void Arduino::reset() {
	WriteSerial2(_command_reset);
}

void Arduino::calibrate() {
	WriteSerial2(_command_calibrate);
}

void Arduino::sync_package(ArduinoSyncPackage* _pack) {
// Purpose: Synchronize geometry package with arduino (Min/max values, etc...)
// Return:	0 if successful, 1 otherwise

	int property = 1;
	try{
		while(property <= 6){
			WriteSerial2(_command_sync_package);
			int Value = atoi(this->ReadSerial2().c_str());

			switch(property){
			case 1:
				_pSyncPackage->trans.min_um = Value;
				break;
			case 2:
				_pSyncPackage->trans.max_um = Value;
				break;
			case 3:
				_pSyncPackage->trans.steps = Value;
				break;
			case 4:
				_pSyncPackage->azimu.min_mdeg = Value;
				break;
			case 5:
				_pSyncPackage->azimu.max_mdeg = Value;
				break;
			case 6:
				_pSyncPackage->azimu.steps = Value;
				break;
			}
			wxThread::Sleep(50);
			property++;
		}
	}
	catch(boost::system::system_error &err){
		throw std::runtime_error("Fehler beim Syncronisieren der Geometrie-Einstellungen.");
	}
}

