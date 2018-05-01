#include "NetworkFsm.h"

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

Packet NetworkFsm::listen()
{
	Packet Packet;
	/*correr fsm hasta que vuelva al estado inicial de esperando evento o tire error, y si recibis un paquete lo retorneas*/
	return Packet;
}




void waitReadyConfirm(void* data)
{

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
void sendAck(void * data)	//VERSIONES BASICAS DESPUES VER COMO METER EN EL DISPATCHER
{
	using namespace gameSettings;
	
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

