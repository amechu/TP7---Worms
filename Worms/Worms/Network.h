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
	Network();
	~Network();
	netData netData;                  
	NetworkFsm networkFsm;
	//Client * Client;
	//Server * Server;
	void networkProtocol();
	Packet fetchToSend();
	Packet fetchRecieved();
	void pushToSend(Packet);
	void pushToRecieved(Packet);


private:
	std::queue<Packet> toSend;
	std::queue<Packet> Recieved;
};

