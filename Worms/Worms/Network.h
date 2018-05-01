#pragma once

#include <iostream>
#include "netData.h"
#include "Server.h"
#include "Client.h"
#include "Packet.h"
#include "NetworkFsm.h"
#include "Packager.h"
#include <string>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <queue>

class Network
{
public:
	Network(netData * net, std::string port);
	~Network();  

	NetworkFsm networkFsm;

	void networkProtocol();
	Packet fetchToSend();
	Packet fetchRecieved();

	void pushToSend(Packet);
	void pushToRecieved(Packet);

	void createLineServer();
	void createLineClient(std::string host, std::string port);

private:

	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::resolver* resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::ip::tcp::acceptor* acceptor;

	netData * net;

	std::queue<Packet> toSend;
	std::queue<Packet> Recieved;
};

