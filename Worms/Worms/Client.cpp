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

void Client::connect(const char * host, const char * port)
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
*/