#include "NetworkFsm.h"
#include "Network.h"

using namespace std;

NetworkFsm::NetworkFsm()
{
	estado = READYTOCONNECT;		//seteo siempre para despues mandarle el i'm ready
}

NetworkFsm::~NetworkFsm()
{
}

Packet NetworkFsm::listen(Network* network)
{
	Packet Packet;
	std::string string;
	bool check = false, good = false;
	int i;
	
	do {
		if (estado == READYTOCONNECT) {
			if (network->net->getIfHost()) {
				network->sendInfo(Packet.makePacket(IAMRDY, 0, 0, gameSettings::WormInitialPosition));
				this->estado = WAIT_READY;
				Packet = waitReady(network);
				if (Packet.header == IAMRDY) {
					run(READY_RECEIVED, &events, network);
				}
				else {
					run(NET_ERROR, &events, network);
				}
			}
			else {
				Packet = waitReady(network);
				if (Packet.header == IAMRDY) {
					run(READY_RECEIVED, &events, network);
				}
				else {
					run(NET_ERROR, &events, network);
				}
			}
		}
		else if (estado == WAIT_REQUEST) {

			Packet = waitRequest(network);

		}
		else if (estado == WAIT_ACK) {

			Packet = waitAck(network);

		}
	} while (estado != WAIT_REQUEST);

	return Packet;
}

void NetworkFsm::say(Packet packet, Network* network)
{
	estado = WAIT_ACK;
	network->sendInfo(packet.makePacket(packet.header, packet.action, packet.id, packet.pos));
	if (packet.header == QUIT_) {
		setEvent(QUIT_REQUEST_RECEIVED);
	}

}

Packet NetworkFsm::run(int ev, void* data, Network* network)
{
	Packet Packet;
	setLastEvent(events.Event);
	setEvent(ev);
	Packet = tabla[estado][ev].action(data, network, this);
	estado = tabla[estado][ev].nextState;
	return Packet;
};

Packet NetworkFsm::waitReady(Network* network) {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = network->getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(IAMRDY)) {
				good = true;
				aux += (string.c_str())[2];
				aux += (string.c_str())[1];
				pos = stoi(aux);
				Packet.header = IAMRDY;
				Packet.pos = pos;
			}
			else {
				run(NET_ERROR, &events, network);
				Packet.header = ERROR_;
			}
		}
		else
			i++;
	}
	if (!good) {
		run(TIMEOUT2, &events, network);
		Packet.header = ERROR_;
	}

	return Packet;
}

Packet NetworkFsm::waitRequest(Network* network) {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = network->getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(MOVE_)) {
				good = true;
				aux += (string.c_str())[5];
				aux += (string.c_str())[4];
				aux += (string.c_str())[3];
				aux += (string.c_str())[2];
				this->packet.header = MOVE_;
				this->packet.action = (string.c_str())[1];
				this->packet.id = stoi(aux);
				run(MOVE_REQUEST_RECEIVED, &events, network);
				Packet = this->packet;
			}
			else if ((string.c_str())[0] == (char)(IAMRDY) || (string.c_str())[0] == (char)(ACK_) || (string.c_str())[0] == (char)(ERROR_) || (string.c_str())[0] == (char)(ACKR_)) {
				good = true;
				Packet = run(NET_ERROR, &events, network);
			}
			else if ((string.c_str())[0] == (char)(QUIT_)) {
				Packet = run(QUIT_REQUEST_RECEIVED, &events, network);
			}
		}
		else
			i++;
	}
	if (!good) {
		Packet.header = 0;
	}
	
	return Packet;
}

Packet NetworkFsm::waitAck(Network* network) {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = network->getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(ACK_)) {
				good = true;
				aux += (string.c_str())[4];
				aux += (string.c_str())[3];
				aux += (string.c_str())[2];
				aux += (string.c_str())[1];
				if (getEvent() == READY_RECEIVED) {
					if (!(stoi(aux) == 0)) {
						run(NET_ERROR, &events, network);
					}
					else {
						Packet.header = ACK_;
						Packet.id = 0;
					}
				}
				else if (getEvent() == QUIT_REQUEST_RECEIVED) {
					if (!(stoi(aux) == 0)) {
						run(NET_ERROR, &events, network);
					}
					else {
						Packet.header = QUIT_;
						Packet.id = 0;
					}
				}
				else {
					if (stoi(aux) == this->packet.id) {
						run(ACK_RECEIVED, &events, network);
					}
				}
			}
			else {
				good = true;
				Packet = run(NET_ERROR, &events, network);
			}
		}
		else
			i++;
	}
	if (!good) {
		Packet.header = 0;
	}

	return Packet;
}

int NetworkFsm::getEvent()
{
	return events.Event;
}

int NetworkFsm::getLastEvent()
{
	return events.LastEvent;
}


void NetworkFsm::setEvent(int ev)
{
	events.Event = ev;
}

void NetworkFsm::setLastEvent(int lastev)
{
	events.LastEvent = lastev;
}

int NetworkFsm::getState()
{
	return estado;
}

//Callbacks

Packet sendReady(void * data, Network * network, NetworkFsm * netfsm)
{	
	Packet Packet;
	Packet.header = 0;
	network->sendInfo(Packet.makePacket(IAMRDY, 0, 0, gameSettings::WormInitialPosition + 400));
	return Packet;
}

Packet sendAckr(void * data, Network * network, NetworkFsm * netfsm)
{
	Packet Packet;
	Packet.header = 0;
	network->sendInfo(Packet.makePacket(ACK_, 0, 0, 0));
	return Packet;
}

Packet rest(void * data, Network * network, NetworkFsm * netfsm)
{
	Packet Packet;
	Packet.header = 0;
	return Packet;
}

Packet errorComm(void * data, Network * network, NetworkFsm * netfsm)
{
	Packet Packet;
	Packet.header = ERROR_;
	return Packet;
}

Packet sendAck(void * data, Network * network, NetworkFsm * netfsm)
{
	Packet Packet;
	Packet.header = 0;
	if (netfsm->getEvent() == MOVE_REQUEST_RECEIVED) {
		network->sendInfo(Packet.makePacket(ACK_, 0, netfsm->packet.id, 0));
	}
	else if (netfsm->getEvent() == QUIT_REQUEST_RECEIVED) {
		network->sendInfo(Packet.makePacket(ACK_, 0, 0, 0));
		Packet.header = QUIT_;
	}
	return Packet;
}

Packet reSend(void * data, Network * network, NetworkFsm * netfsm)
{
	Packet Packet;
	Packet.header = 0;
	return Packet; //pensar
}