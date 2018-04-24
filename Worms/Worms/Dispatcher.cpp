#include "Dispatcher.h"
#include "AllegroTools.h"


Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::Dispatch(Event Event, Scenario* Scene, AllegroTools* allegroTools)
{
	switch (Event.type) {
		case JUMP: {
			Scene->Jump(Event, allegroTools);
			break;
		}
		case TOGGLE: {
			Scene->Toggle(Event, allegroTools);
			break;
		}
		case RIGHT: {
			Scene->moveRight(Event, allegroTools);
			break;
		}
		case LEFT: {
			Scene->moveLeft(Event, allegroTools);
			break;
		}
		case REFRESHRIGHT: {
			Scene->moveRight(Event, allegroTools);
			Scene->Refresh(allegroTools);
			break;
		}
		case REFRESHLEFT: {
			Scene->moveLeft(Event, allegroTools);
			Scene->Refresh(allegroTools);
			break;
		}
		case REFRESH: {
			Scene->Refresh(allegroTools);
			break;
		}
		case QUIT: {
			//Mandar paquete de quit &0
			//Decir disconnecting.. en pantalla &0
			//Esperar ACK &0
			//Cerrar programa &0
			break;
		}
		case NOEVENT: {
			break;
		}
	}
}
