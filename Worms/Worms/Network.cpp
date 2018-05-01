#include "Network.h"


Network::Network(netData * net, std::string port)
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
	resolver = new boost::asio::ip::tcp::resolver(*IO_handler);

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
	socket->non_blocking(true);

	acceptor->accept(*socket);
}

void Network::createLineClient(std::string host, std::string port)
{
	try {

		socket->non_blocking(true);

		endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(host, port));

		boost::asio::connect(*socket, endpoint);

	}
	catch (std::exception & e) 
	{
		std::cout << "Error al intentar conectar" << std::endl;
		net->setIfHost(gameSettings::QUITTER);
	}
}