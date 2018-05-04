#include "Sender.h"

Sender::Sender(Network* network)
{
	this->network = network;
}


Sender::~Sender()
{
}

void Sender::update(void * subject, void* tool)
{
	Scenario* Scene = (Scenario*)subject;

	if ((Scene->getLastAction()).origin == LOCAL) {
		switch ((Scene->getLastAction()).id) {
		case LEFT:
			Packet.header = MOVE_;
			Packet.action = ACTIONLEFT;
			Packet.id = (rand() % (0xFFFFFFFF + 1));
			break;
		case RIGHT:
			Packet.header = MOVE_;
			Packet.action = ACTIONRIGHT;
			Packet.id = (rand() % (0xFFFFFFFF + 1));
			break;
		case JUMP:
			Packet.header = MOVE_;
			Packet.action = ACTIONJUMP;
			Packet.id = (rand() % (0xFFFFFFFF + 1));
			break;
		case TOGGLELEFT:
		case TOGGLERIGHT:
			Packet.header = MOVE_;
			Packet.action = ACTIONTOGGLE;
			Packet.id = (rand() % (0xFFFFFFFF + 1));
			break;
		case QUITLOCAL:
			Packet.header = QUIT_;
		}
	}

	network->networkFsm.say(Packet, network);
}
