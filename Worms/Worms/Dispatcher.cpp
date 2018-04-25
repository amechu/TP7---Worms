#include "Dispatcher.h"
#include "AllegroTools.h"
#include <iostream>


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
			Scene->setWormState(Event, WormState::Walking);
			Scene->directWorm(Event, WormDirection::Right);
			Scene->Refresh(allegroTools, false);
			break;
		}
		case REFRESHLEFT: {
			Scene->setWormState(Event, WormState::Walking);
			Scene->directWorm(Event, WormDirection::Left);
			Scene->Refresh(allegroTools, false);
			break;
		}
		case REFRESH: {
			Scene->Refresh(allegroTools, true);
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
