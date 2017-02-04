/*
 Copyright 2016 Florian Otte
 
 This file is part of Mneme v0.1 (Mayflower).
 Filename: hw_servo_control.h
 */
#ifndef DEVICE_ARDUINO_H_
#define DEVICE_ARDUINO_H_

#include "serial.h"

namespace arduino{
	extern std::string com_port_arduino;
}


class Arduino: public SerialDevice {
public:
	Arduino();
	~Arduino();

	void Init( std::string port );

	int light_led( bool ON );

	void set_tpos_micrometer( int Value );
	void set_tpos_au( int Value );
	void set_apos_millidegree( int Value );
	void set_apos_au( int Value );

	int get_tpos_micrometer();
	int get_tpos_au( );
	int get_tpos_setpoint_au( );
	int get_apos_millidegree( );
	int get_apos_au( );
	int get_apos_setpoint_au( );

	std::string get_status();
	std::string get_version();

	void new_zero();
	void reset();
	void calibrate();

protected:

	struct ArduinoSyncPackage{
		struct strans{
			int min_um;
			int max_um;
			int steps;
		} trans;
		struct sazimu{
			int min_mdeg;
			int max_mdeg;
			int steps;
		} azimu;
	} *_pSyncPackage;

	void sync_package( ArduinoSyncPackage* _pack);

	std::string _command_led_on;
	std::string _command_led_off;
	std::string _command_status;
	std::string _command_new_zero;
	std::string _command_trans_pos;
	std::string _command_azimu_pos;
	std::string _command_get_trans_pos;
	std::string _command_get_azimu_pos;
	std::string _command_get_trans_pos_setpoint;
	std::string _command_get_azimu_pos_setpoint;
	std::string _command_reset;
	std::string _command_calibrate;
	std::string _command_version;
	std::string _command_sync_package;
};

#endif /* DEVICE_ARDUINO_H_ */
