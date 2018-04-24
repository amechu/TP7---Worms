#pragma once

/*

#include <string>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "Timer.h"

class Server
{
public:
	Server();
	~Server();
	void listen();
	std::string getInfoTimed(int limitInMs);

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* serverSocket;
	boost::asio::ip::tcp::acceptor* serverAcceptor;
	const std::string TIMEOUT = "timeout";
};

*/