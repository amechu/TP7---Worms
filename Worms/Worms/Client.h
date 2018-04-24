#pragma once

/*

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
	void connect(const char * host, const char * port);
	bool sendMessage(std::string msg, int limitInMs);

private:
	boost::asio::io_service* IOHandler;
	boost::asio::ip::tcp::socket* clientSocket;
	boost::asio::ip::tcp::resolver* clientResolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};

*/