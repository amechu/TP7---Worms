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

void NetworkFsm::say(Packet Packet)
{
	/* mandar algo por networking */
}

Packet NetworkFsm::listen(Network* network)
{
	Packet Packet;
	std::string string;
	bool check = false, good = false;
	int i;
	
	if (estado == READYTOCONNECT) {
		if (network->net->getIfHost()) {
			network->sendInfo(Packet.makePacket(IAMRDY, 0, 0, gameSettings::LeftWall + 400));
			run(SEND_READY, &events);
		}
		else {
			while (i < 5 || !check) {
				string = network->getInfoTimed(20);
				if (string != "timeout") {
					check = true;
					if ((string.c_str())[0] == (char)(0x20)) {
						good = true;
						run(RECIEVE_READY, &events);
					}
					else {
						run(NET_ERROR, &events);
					}
				}
				else
					i++;
			}
			if (!good) {
				run(TIMEOUT2, &events);
			}
		}
	}

	//hasta aca seria el handshake? hay que ver que este bien.
	//a partir de aca hay que hacer que la fsm corra (es decir escucharla) y mandar ack (lo haria solo cuando se hace run() con el evento de move) para que vuelva al estado de wait_request.
	//y capturar y devolver aquel paquete move si es que llega.


	return Packet;
}




void waitReadyConfirm(void* data, Network* network, NetworkFsm* netfsm)
{
	int i = 0;
	bool check = false, good = false;
	std::string string;

	while (i < 5 || !check) {
		string = network->getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(0x20)) {
				good = true;
				netfsm->run(RECIEVE_READY, &(netfsm->events));
			}
			else {
				netfsm->run(NET_ERROR, &(netfsm->events));
			}
		}
		else
			i++;
	}
	if (!good) {
		netfsm->run(TIMEOUT2, &(netfsm->events));
	}
}

void errorComunication(void* data)
{
	//si llega un error corto todo

	data_t*p = (data_t*)data;
	p->error = true;
	p->leave = true;
	p->quitall = true;
}
void waitMoveConfirm(void* data)
{
	//enviar el paquete 
	//despues esperarlo
}
void quitAnswer(void* data)
{
//	cout << "closing program" << endl;
	data_t* p = (data_t*)data;
	p->leave = true;
	p->quitall = true;

}
void sendAck(void * data, Network* network, NetworkFsm* netfsm)	//VERSIONES BASICAS DESPUES VER COMO METER EN EL DISPATCHER
{
	Packet Packet;
	network->sendInfo(Packet.makePacket(IAMRDY, 0, 0, gameSettings::LeftWall + 400));
	netfsm->run(SEND_READY, &(netfsm->events));
}
void AckRecieved(void* data)
{
	
	//std::cout << "ACK recieved and matched the ID. Leaving FSM" << std::endl;
	data_t * p = (data_t*)data;
	p->leave = true;
}
void reSend(void* data)
{

}
void doNothing(void* data)
{

}

void NetworkFsm::run(int ev, void* data)
{
	(events.LastEvent) = (events.Event);
	events.Event = ev;
	tabla[estado][ev].action(data);
	estado = tabla[estado][ev].nextState;
};

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

