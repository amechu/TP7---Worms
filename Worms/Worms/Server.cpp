#include "Server.h"

/*

Server::Server()
{
	this->IO_handler = new boost::asio::io_service();
	this->serverSocket = new boost::asio::ip::tcp::socket(*(this->IO_handler));
	this->serverAcceptor = new boost::asio::ip::tcp::acceptor(*(this->IO_handler),
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
}


Server::~Server()
{
	this->serverAcceptor->close();
	this->serverSocket->close();
	delete this->serverAcceptor;
	delete this->serverSocket;
	delete this->IO_handler;
}

void Server::listen()
{
	this->serverAcceptor->accept(*(this->serverSocket));
}

std::string Server::getInfoTimed(int limitInMs)
{	
	Timer timer;
	char buffer[1 /*DEBUG, pensar tamano de paquete*/ /*];
	size_t lenght = 0;
	boost::system::error_code error;

	timer.start();

	bool timeout = false;

	do {

		lenght = this->serverSocket->read_some(boost::asio::buffer(buffer), error);
		timer.stop();

		if (timer.getTime() > limitInMs && lenght == 0) { // Pido que lenght == 0 asi no lo paro mientras esta mandando
			timeout = true;
		}

	} while (error && !timeout);
	std::string retValue;

	if (!timeout) {
		buffer[lenght] = 0;
		retValue = buffer;
	}
	else
		retValue = TIMEOUT;

	return retValue;
}

*/