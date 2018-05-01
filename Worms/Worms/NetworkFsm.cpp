#include "NetworkFsm.h"

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

}
void waitMoveConfirm(void* data)
{

}
void quitAnswer(void* data)
{

}
void sendAck(void * data)	//VERSIONES BASICAS DESPUES VER COMO METER EN EL DISPATCHER
{
	using namespace gameSettings;

	/*

	std::string message;

	if ((events.Event) == ACKS)
	{
		packet.header = ACK;
		packet.id = 1;	//pq tengo que mandar a externo y no se si va la ip o no
		message=packet.makePacket();
		//agregar funcion que envia el paquete 
	}
	*/
	
}
void doStuff(void* data)
{

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

