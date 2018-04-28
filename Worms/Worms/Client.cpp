#include "Client.h"

/*
Client::Client()
{
	this->IOHandler = new boost::asio::io_service();
	this->clientSocket = new boost::asio::ip::tcp::socket(*IOHandler);
	this->clientResolver = new boost::asio::ip::tcp::resolver(*IOHandler);
}


Client::~Client()
{
	this->clientSocket->close();
	delete this->clientResolver;
	delete this->clientSocket;
	delete this->IOHandler;
}

void Client::connect(std::string host, std::string port)
{
	auto q = boost::asio::ip::tcp::resolver::query(host, port);
	this->endpoint = clientResolver->resolve(q);
	boost::asio::connect(*clientSocket, endpoint);
	clientSocket->non_blocking(true);
}

bool Client::sendMessage(std::string msg, int limitInMs)
{
	Timer timer;
	size_t lenght = 0;
	boost::system::error_code error;
	bool timeout = false;

	timer.start();

	do {

		lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.size()), error);
		timer.stop();

		if (timer.getTime() > limitInMs && lenght == 0) //Si se excede del limite de tiempo y no mando nada. (si length no es cero, todavia manda cosas)
			timeout = true;

	} while (error && !timeout);

	return !timeout;

}

std::string Client::getInfoTimed(int limitInMs)
{
	Timer timer;
	char buffer[1 /*&0, pensar tamano de paquete, cambiar para que funque con client y no server];
	size_t lenght = 0;
	boost::system::error_code error;

	timer.start();

	bool timeout = false;

	do {

	//	lenght = this->serverSocket->read_some(boost::asio::buffer(buffer), error);
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