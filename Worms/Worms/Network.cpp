#include "Network.h"


Network::Network(Client * cli, Server * ser)
{
	this->cli = cli;
	this->ser = ser;
}


Network::~Network()
{
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
