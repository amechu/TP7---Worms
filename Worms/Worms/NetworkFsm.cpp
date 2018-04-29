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
