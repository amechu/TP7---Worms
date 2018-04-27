#pragma once

#include "netData.h"
#include "Server.h"
#include "Client.h"

class Network
{
public:
	Network();
	~Network();
	netData netData;
	Client * Client;
	Server * Server;
};

