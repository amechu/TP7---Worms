#include "EventGenerator.h"
#include "GameSettings.h"

#define WALKDURATION 1000
#define TIMEFIX 200

EventGenerator::EventGenerator()
{
}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::pushEvent(Event event)
{
	eventQueue.push(event);
}

Event EventGenerator::fetchEvent()
{
	Event returnVal = eventQueue.front();
	eventQueue.pop();
	return returnVal;
}

Event EventGenerator::transformAllegroEvent(AllegroTools * allegroTools)
{
	ALLEGRO_EVENT allegroEvent;
	Event Event = { NOEVENT , 0 };

	if (al_get_next_event(allegroTools->Queue, &allegroEvent)) {

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			Event.type = QUIT;
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			Timer.stop();
			if (activeTimer[gameSettings::Left] == true && Timer.getTime() >= 100) {
				if (Timer.getTime() >= (firstMove ? WALKDURATION + TIMEFIX : WALKDURATION)) {
					Timer.start();
					sentMove = false;
					firstMove = false;
				}
				else {
					Event.type = REFRESH;
				}
				if (!sentMove) {
					Event.type = REFRESHLEFT;
					sentMove = true;
				}
				else {
					Event.type = REFRESH;
				}
			}
			else if (activeTimer[gameSettings::Right] == true && Timer.getTime() >= 100) {
				if (Timer.getTime() >= (firstMove? WALKDURATION + TIMEFIX : WALKDURATION)) {
					Timer.start();
					sentMove = false;
					firstMove = false;
				}
				else {
					Event.type = REFRESH;
				}
				if (!sentMove) {
					Event.type = REFRESHRIGHT;
					sentMove = true;
				}
				else {
					Event.type = REFRESH;
				}
			}
			else {
				if (activeTimer[gameSettings::Jump] == true && Timer.getTime() >= 640) {
					activeTimer[gameSettings::Jump] = false;
				}
				Event.type = REFRESH;
			}
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Left]) {
				if (activeTimer[gameSettings::Left] == false && activeTimer[gameSettings::Right] == false && activeTimer[gameSettings::Jump] == false) {
					activeTimer[gameSettings::Left] = true;
					Timer.start();
				}
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Right]) {
				if (activeTimer[gameSettings::Left] == false && activeTimer[gameSettings::Right] == false && activeTimer[gameSettings::Jump] == false) {
					activeTimer[gameSettings::Right] = true;
					Timer.start();
				}
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Jump]) {
				if (activeTimer[gameSettings::Left] == false && activeTimer[gameSettings::Right] == false) {
					activeTimer[gameSettings::Jump] = true;
					Event.type = JUMP;
					Timer.start();
				}
			}
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Left]) {
				if (activeTimer[gameSettings::Left] == true) {
					if (Timer.getTime() < 100) {
						Event.type = TOGGLELEFT;
					}
				}
					activeTimer[gameSettings::Left] = false;
					sentMove = false;
					firstMove = true;
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Right]) {
				if (activeTimer[gameSettings::Right] == true) {
					if (Timer.getTime() < 100) {
						Event.type = TOGGLERIGHT;
					}
				}
					activeTimer[gameSettings::Right] = false;
					sentMove = false;
					firstMove = true;
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Jump]) {
				//Nothing to do here
			}
		}
	}
	else {
		Event.type = NOEVENT;
	}

	return Event;
}

Event EventGenerator::transformNetworkEvent(Network* Network)
{
	Event Event = { NOEVENT, 1 }; // lo puse en mausculas pq hace lio con otro event de windows
	Packet Packet;
	Packet = Network->fetchRecieved();

	if (Packet.header == MOVE )
	{
		if (Packet.action == (gameSettings::Left))
		{
			Event.type = LEFT;
		}
		else if (Packet.action == (gameSettings::Right))
		{
			Event.type = RIGHT;
		}
		else if (Packet.action == (gameSettings::Jump))
		{
			Event.type = JUMP;
		}
		else if (Packet.action == (gameSettings::Toggle))
		{
			Event.type = TOGGLE;
		}
	}
	else if ((Packet.header == ACK) && (Packet.id == 0)) // caso del primer i'm ready
	{
		Event.type = NEWWORM; //ME LLEGO EL ACK QUE ENTENDIO CREO EL WORM
	}
	else if ((Packet.header == ACK) && (Packet.id != 0))//caso ack de los demas
	{
		Event.type = SPEAK;		//provisional
	}
	else if ((Packet.header == I_AM_READY))	//validar posicion??
	{
		Event.type = HEAR;
	}
	else if ((Packet.header == ERRORNET))	//LO TIRE DE ONDA PERO HAY QUE CORREGIRLO ESTE ES POR LOS TIMERS
	{
		// no se si poner LOS timer aca para ver si me llegan otros
	}
	else if ((Packet.header == QUITPACKET))
	{
		Event.type = QUIT;
	}
	else
	{
		Event.type = NOEVENT;
	}
	return Event;
}

void EventGenerator::checkIncomingEvents(AllegroTools * allegroTools, Network * Network)
{
	Network->networkProtocol();
	pushEvent(transformAllegroEvent(allegroTools));
	pushEvent(transformNetworkEvent(Network));
}

