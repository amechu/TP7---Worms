#include "Network.h"



Network::Network()
{
}


Network::~Network()
{
}

void Network::networkProtocol()
{

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
