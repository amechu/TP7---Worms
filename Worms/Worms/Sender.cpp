#include "Sender.h"

Sender::Sender()
{
}


Sender::~Sender()
{
}

void Sender::update(void * subject, void* tool)
{
	//me fijo si el cambio en scene fue relevante para mi (si lo que ccambio fue un worm local) (LASTACTION.ORIGIN == LOCAL?) ENTONCES HAGO.

	//si lo fue, hago cosas. (mando por network lo que cambio) &0 
}

void Sender::send(std::string package)
{
}
