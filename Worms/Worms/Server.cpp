#include "Server.h"


Server::Server(std::string port)
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


void Server::createLineServer()
{
	serverSocket->non_blocking(true);

	serverAcceptor->accept(*serverSocket);
}

/*
std::string Server::getInfoTimed(int limitInMs)
{	
	Timer timer;
	char buffer[1 /*DEBUG, pensar tamano de paquete];
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

bool Server::sendInfoTimed(std::string msg, int limitInMs)
{ //&0 hacer  que funque con server y no client
	Timer timer;
	size_t lenght = 0;
	boost::system::error_code error;
	bool timeout = false;

	timer.start();

	do {

	//	lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.size()), error);
		timer.stop();

		if (timer.getTime() > limitInMs && lenght == 0) //Si se excede del limite de tiempo y no mando nada. (si length no es cero, todavia manda cosas)
			timeout = true;

	} while (error && !timeout);

	return !timeout;
}
*/