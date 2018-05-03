#include "Network.h"


Network::Network(netData * net, std::string port)
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	

	this->net = net;
}


Network::~Network()
{
	acceptor->close();
	socket->close();
	delete resolver;
	delete acceptor;
	delete socket;
	delete IO_handler;
}

void Network::networkProtocol()
{
	Packet Packet;
	Packet = networkFsm.listen(); //corre la fsm hasta que vuelva al estado inicial.
	pushToRecieved(Packet);
	if (!toSend.empty()) { //si hay algo para decir, lo manda
		Packet = fetchToSend();
		networkFsm.say(Packet);
	}

}

Packet Network::fetchToSend()
{
	Packet returnVal = toSend.front();
	toSend.pop();
	return returnVal;
}

Packet Network::fetchRecieved()
{
	Packet returnVal = Recieved.front();
	Recieved.pop();
	return returnVal;
}

void Network::pushToSend(Packet packet)
{
	toSend.push(packet);
}

void Network::pushToRecieved(Packet packet)
{
	Recieved.push(packet);
}

void Network::createLineServer()
{
	acceptor->accept(*socket);
	socket->non_blocking(true);
}

void Network::createLineClient(std::string host, std::string port)
{
	try {


		endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(host, port));

		boost::asio::connect(*socket, endpoint);

		socket->non_blocking(true);
	}
	catch (std::exception & e) 
	{
		std::cout << "Error al intentar conectar" << std::endl;
		net->setIfHost(gameSettings::QUITTER);
	}
}

std::string Network::getInfoTimed(int limitInMs)
{
	Timer timer;
	char buffer[6];
	size_t lenght = 0;
	boost::system::error_code error;

	timer.start();

	bool timeout = false;

	do 
	{

		lenght = this->socket->read_some(boost::asio::buffer(buffer), error);
		timer.stop();

		if (timer.getTime() > limitInMs && lenght == 0) 
		{														// Pido que lenght == 0 asi no lo paro mientras esta mandando
			timeout = true;
		}

	} while (error && !timeout);

	std::string retValue;

	if (!timeout) 
	{
		buffer[lenght] = 0;
		retValue = buffer;
	}
	else
		retValue = TIMEOUT;

	return retValue;
}

void Network::sendInfo(std::string msg)
{																//&0 hacer  que funque con server y no client
	size_t lenght = 0;
	boost::system::error_code error;

	do {

		lenght = this->socket->write_some(boost::asio::buffer(msg, msg.size()), error);

	} while (error);

}

void Network::acceptOrResolve(std::string port)
{
	if (net->getIfHost() == gameSettings::HOST)
	{
		acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
	}
	else
	{
		resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	}
}