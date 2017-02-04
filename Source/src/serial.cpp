/*
 Copyright 2016 Florian Otte
 
 This file is part of Mneme v0.1 (Mayflower).
 Filename: serial.cpp
 */
#include "serial.h"

#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/core/ref.hpp>



SerialDevice::SerialDevice( int SERVICE_RESTART_DELAY, int TIMEOUT_READ,
		int TIMEOUT_WRITE, int NEXT_MESSAGE_DELAY  ):
_serial(_io), _timeout(_io)
{
	_times.SERVICE_RESTART_DELAY =  SERVICE_RESTART_DELAY ;
	_times.TIMEOUT_READ = TIMEOUT_READ;
	_times.TIMEOUT_WRITE = TIMEOUT_WRITE;
	_times.NEXT_MESSAGE_DELAY = NEXT_MESSAGE_DELAY;
	//_timeout.expires_at(boost::posix_time::pos_infin);
	// Start the persistent actor that checks for deadline expiry.
	//check_deadline();
}

SerialDevice::~SerialDevice() {

	// Suppress exceptions by providing an error_code type variable
	boost::system::error_code ec;
	_serial.close(ec);
}

void SerialDevice::OpenPort(std::string port, unsigned int baud_rate) {
// Purpose: 	Open serial port and set port options
// Return:		void
// Error:		Might throw an exception of type boost::system::system_error

		if (_serial.is_open())
			_serial.close();
		_serial.open(port);
		_serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
		_serial.set_option(boost::asio::serial_port_base::character_size(8));
}

void SerialDevice::set_new_timing( TIMING NewTiming ) {
	_times = NewTiming;
}

SerialDevice::TIMING SerialDevice::get_timing(){
	return _times;
}

void SerialDevice::WriteSerial( std::string s ) {
// Purpose: Write to serial device and block until operation is finished
// Return:	void
// Error:	Might throw an exception of type boost::system::system_error

		boost::system::error_code 	ec = boost::asio::error::would_block;
		std::size_t 				length = 0;
		_timeout.expires_from_now(boost::posix_time::milliseconds(_times.TIMEOUT_WRITE));

		// add carriage return symbol to string s
		s = s + (char)13;
		boost::asio::async_write(_serial, boost::asio::buffer(s.c_str(), s.size()),
				boost::bind(&SerialDevice::handler_io, _1, _2, &ec, &length));

		do _io.run_one(); while (ec == boost::asio::error::would_block);

		if (ec)
			throw boost::system::system_error(ec, "Serial write timeout");
		else
			return;
}

std::string SerialDevice::ReadSerial() {
// Purpose: Read from serial device with timeout and block until operation is finished
// Return:	std::string s of length s.length()-1 (cut carriage return symbol)
// Error:	Might throw an exception of type boost::system::system_error



	boost::asio::streambuf 		buffer;
	boost::system::error_code 	ec = boost::asio::error::would_block;
	std::size_t 				length = 0;
	_timeout.expires_from_now(boost::posix_time::milliseconds(_times.TIMEOUT_READ));

	char cr = 13;
	boost::asio::async_read_until(_serial, buffer, cr, boost::bind(&SerialDevice::handler_io, _1, _2, &ec, &length));
	_io.reset();
	do _io.run_one(); while (ec == boost::asio::error::would_block);
	if(ec) throw boost::system::system_error(ec, "Serial read timeout");
	std::string line;
	std::istream is(&buffer);
	std::getline(is, line);


	// Cut carriage return symbol
	line = line.substr(0, line.length() -1);
	return line;

}

void SerialDevice::WriteSerial2( std::string s ) {

	std::size_t 	bytes_written = 0;
	s = s + (char)13;

	// boost::bind method: class member function read_callback has
	// implicit 'this' argument
	_serial.async_write_some(
			boost::asio::buffer(s.c_str(), s.size()),
			boost::bind(
					&io_callback,
					this,
					boost::ref( bytes_written ),
					boost::ref( _timeout ),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred) );

	_timeout.expires_from_now(
				boost::posix_time::milliseconds( _times.TIMEOUT_WRITE ));

	// boost::bind method: class member function wait_callback has
	// implicit 'this' argument
	_timeout.async_wait(
			boost::bind(&wait_callback,
					this,
					boost::ref( _serial ),
					boost::asio::placeholders::error) );

	_io.reset();
	Sleep( _times.SERVICE_RESTART_DELAY);
	_io.run();  // will block until async callbacks are finished

}

std::string SerialDevice::ReadSerial2() {

	char 			my_buffer[ 64 ];
	std::size_t 	bytes_read = 0;

	// boost::bind method: class member function read_callback has
	// implicit 'this' argument
	_serial.async_read_some(
			boost::asio::buffer( my_buffer ),
			boost::bind(
					&io_callback,
					this,
					boost::ref( bytes_read ),
					boost::ref( _timeout ),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred) );

	_timeout.expires_from_now(
			boost::posix_time::milliseconds( _times.TIMEOUT_READ ));

	// boost::bind method: class member function wait_callback has
	// implicit 'this' argument
	_timeout.async_wait(
			boost::bind(&wait_callback,
					this,
					boost::ref( _serial ),
					boost::asio::placeholders::error) );

	_io.reset();
	Sleep( _times.SERVICE_RESTART_DELAY);
	_io.run();  // will block until async callbacks are finished


	std::string return_string( my_buffer );
	return return_string.substr( 0, bytes_read -1 ); // -1: cut carriage return symbol
}

void SerialDevice::check_deadline(){
// Purpose: Check if timer deadline has passed and reset io_service if so
// Return:	void
// Error:	Might throw an exception of type boost::system::system_error

	if(_timeout.expires_at() <= boost::asio::deadline_timer::traits_type::now())
	{
		// The deadline has passed
		_serial.cancel();
		_timeout.expires_at(boost::posix_time::pos_infin);
	}
	_timeout.async_wait(boost::bind(&SerialDevice::check_deadline, this));
}

void SerialDevice::handler_io(const boost::system::error_code& ec,
		std::size_t length, boost::system::error_code* out_ec,
		std::size_t* out_length) {
	*out_ec = ec;
	*out_length = length;
}

void SerialDevice::io_callback(
		std::size_t& my_bytes_transferred,
		boost::asio::deadline_timer& timeout,
		const boost::system::error_code& error,
		std::size_t bytes_transferred)
{
	if (error || !bytes_transferred)
	{
		// No data was read!
		return;
	}
	my_bytes_transferred = bytes_transferred;
	timeout.cancel();  // will cause wait_callback to fire with an error
}

void SerialDevice::wait_callback(
		boost::asio::serial_port& ser_port,
		const boost::system::error_code& error)
{
  if (error)
  {
    // Data was read and this timeout was canceled
    return;
  }
  ser_port.cancel();  // will cause read_callback to fire with an error
}



