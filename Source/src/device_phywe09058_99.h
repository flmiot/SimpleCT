// ---------------------------------------------------------------------------
// This file is part of SimpleCT. The SimpleCT software is in the public domain,
// furnished "as is", without technical support, and with no warranty, express or
// implied, as to its usefulness for any purpose.
//
// device_phywe09058_99.h
// PHYWE09058_99 class header file.
//
// Author: Florian Otte
// ---------------------------------------------------------------------------

#ifndef DEVICE_PHYWE09058_99_H_
#define DEVICE_PHYWE09058_99_H_

#include "serial.h"

namespace xrayd {
	enum enumDoubles {
		HighVoltage, Current, TPosition, CPosition
	};

	enum enumInts {
		CountRate, HVStatus, CModBusy, KModBusy, ModeRemote, Tint
	};
	enum enumStrings {
		Version, AnodeMaterial
	};

	enum {
		On = true,
		Off = false
	};

	extern std::string com_port_xraydev;
}



// PHYWE x-ray-tube
class PHYWE09058_99 : public SerialDevice {

public:
	PHYWE09058_99();
	virtual ~PHYWE09058_99();

	// The following 3 methods should be all you need from outside this class for basic control
	void Init( std::string port );
	void TurnOn(double VoltageToSet, double CurrentToSet);
	void TurnOff();

	// These functions should not be used from outside (will move to private)
	void set(xrayd::enumInts Property, bool Value);
	void set(xrayd::enumDoubles Property, double Value);

	// Public getters for obtaining information, e.g. count rate
	double get(xrayd::enumDoubles Property);
	int get(xrayd::enumInts Property);
	int get(xrayd::enumInts Property, int TINT);
	std::string get(xrayd::enumStrings Property);

private:
	// set
	// all of these functions return the value they read after setting the arg_Value
	int HVSTAT(bool arg_HVON);
	int CMOD_BUSY(bool arg_CMODBUSY);

	void MODE_REMOTE(bool arg_MODEREMOTE);
	void KMOD_OPEN(bool arg_KMODOPEN);
	void TINT(int arg_TINT);

	double HV(double arg_HV);
	double CURR(double arg_CURR);
	double TPOS(double arg_TPOS);
	double CPOS(double arg_CPOS);

	// get
	int get_HVSTAT();
	int get_CMOD_BUSY();

	double get_HV();
	double get_CURR();
	double get_TPOS();
	double get_CPOS();

	int get_CRT(  int TimeIntervall ); // Parameter TimeIntervall  = measurement integration time

	std::string get_VERSION();
	std::string get_ANOD();
	int get_STAT();

	bool _HVSTAT_ON, _CMOD_BUSY, _KMOD_CLOSE, _MODE_REMOTE;
	double _HV, _CURR, _TPOS, _CPOS;
	int _CRT;
	std::string _VERSION, _ANOD;
};

#endif /* DEVICE_PHYWE09058_99_H_ */
