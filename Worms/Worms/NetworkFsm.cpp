#include "NetworkFsm.h"

NetworkFsm::NetworkFsm()
{
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
void sendAck(void* data)
{

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