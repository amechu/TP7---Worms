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
			Scene->Toggle(Event, allegroTools, WormDirection::Left); //direction unused
			break;
		}
		case TOGGLELEFT: {
			Scene->Toggle(Event, allegroTools, WormDirection::Left);
			break;
		}
		case TOGGLERIGHT: {
			Scene->Toggle(Event, allegroTools, WormDirection::Right);
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
			if (Scene->getWormState(Event) == WormState::Iddle) {
				Scene->setWormState(Event, WormState::Walking);
				Scene->directWorm(Event, WormDirection::Right);
			}
			Scene->Refresh(allegroTools);
			break;
		}
		case REFRESHLEFT: {
			if (Scene->getWormState(Event) == WormState::Iddle) {
				Scene->setWormState(Event, WormState::Walking);
				Scene->directWorm(Event, WormDirection::Left);
			}
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
		case NEWWORM: {
			Scene->createNewWorm(1, { gameSettings::LeftWall + 300, gameSettings::GroundLevel }, WormDirection::Left);
			break;
		}

	}
}
