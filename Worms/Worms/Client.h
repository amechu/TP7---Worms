#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "Timer.h"

class Client
{
public:
	Client();
	~Client();
	void connect(std::string host, std::string port);
	bool sendMessage(std::string msg, int limitInMs); //funcion que manda un paquete.
	std::string getInfoTimed(int limitInMs); //funcion que recibe un paquete

private:
	boost::asio::io_service* IOHandler;
	boost::asio::ip::tcp::socket* clientSocket;
	boost::asio::ip::tcp::resolver* clientResolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	const std::string TIMEOUT = "timeout";
};
