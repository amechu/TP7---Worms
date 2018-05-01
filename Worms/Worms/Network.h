#pragma once

#include "netData.h"
#include "Server.h"
#include "Client.h"
#include "Packet.h"
#include "NetworkFsm.h"
#include "Packager.h"
#include <queue>

class Network
{
public:
	Network(Client * cli, Server * ser);
	~Network();                 
	NetworkFsm networkFsm;
	void networkProtocol();
	Packet fetchToSend();
	Packet fetchRecieved();
	void pushToSend(Packet);
	void pushToRecieved(Packet);
	netData netData;

private:

	Client * cli;
	Server * ser;

	std::queue<Packet> toSend;
	std::queue<Packet> Recieved;
};

