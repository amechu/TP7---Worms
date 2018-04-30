#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include "Timer.h"

class Server
{
public:
	Server(std::string port);
	~Server();
	void listen(); //funcion no bloqueante que ve si algun cliente se quiere conectar
	std::string getInfoTimed(int limitInMs); //funcion que recibe un paquete
	bool sendInfoTimed(std::string msg, int limitInMs); //funcion que manda un paquete.
	void createLineServer();


private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* serverSocket;
	boost::asio::ip::tcp::acceptor* serverAcceptor;
	const std::string TIMEOUT = "timeout";
};
