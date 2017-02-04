#ifndef SERIAL_H_
#define SERIAL_H_

// Win XP
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <boost/asio.hpp>

class SerialDevice {
public:

	SerialDevice( int SERVICE_RESTART_DELAY, int TIMEOUT_READ,
			int TIMEOUT_WRITE, int NEXT_MESSAGE_DELAY );
	virtual ~SerialDevice();
	void OpenPort(std::string port, unsigned int baud_rate);
	struct TIMING {
		int SERVICE_RESTART_DELAY;
		int TIMEOUT_READ;
		int TIMEOUT_WRITE;
		int NEXT_MESSAGE_DELAY;
	};
	void set_new_timing( TIMING NewTiming );
	TIMING get_timing();

	virtual void WriteSerial( std::string s );
	virtual void WriteSerial2( std::string s );
	virtual std::string ReadSerial();
	virtual std::string ReadSerial2();
	//virtual std::string CommandAndListen( std::string s );

protected:

	void check_deadline();
	static void handler_io(
			const boost::system::error_code& ec,
			std::size_t length, boost::system::error_code* out_ec,
			std::size_t* out_length);

	void io_callback(
			std::size_t& bytes_read,
			boost::asio::deadline_timer& timeout,
			const boost::system::error_code& error,
			std::size_t bytes_transferred);

	void wait_callback(
			boost::asio::serial_port& ser_port,
			const boost::system::error_code& error);

	boost::asio::io_service _io;
	boost::asio::serial_port _serial;
	boost::asio::deadline_timer _timeout;

	TIMING _times;

};

#endif /* SERIAL_H_ */
