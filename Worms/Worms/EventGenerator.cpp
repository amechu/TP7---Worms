#include "EventGenerator.h"
#include "GameSettings.h"


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
	Event Event = { 0,0 };

	if (al_get_next_event(allegroTools->Queue, &allegroEvent)) {

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			Event.type = QUIT;
			Event.id = 0;
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			Timer.stop();
			if (activeTimer[gameSettings::Left] == true && Timer.getTime() >= 100) {
					Event.type = REFRESHLEFT;
					Event.id = 0;
			}
			else if (activeTimer[gameSettings::Right] == true && Timer.getTime() >= 100) {
					Event.type = REFRESHRIGHT;
					Event.id = 0;
			}
			else {
				Event.type = REFRESH;
				Event.id = 0;
			}
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Left]) { //&0 no funca esto, no toma la tecla presionada.
				if (activeTimer[gameSettings::Left] == false && activeTimer[gameSettings::Right] == false) {
					activeTimer[gameSettings::Left] = true;
					Timer.start();
				}
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Right]) {
				if (activeTimer[gameSettings::Left] == false && activeTimer[gameSettings::Right] == false) {
					activeTimer[gameSettings::Right] = true;
					Timer.start();
				}
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Jump]) {
				Event.type = JUMP;
				Event.id = 0;
			}
		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Left]) {
				if (Timer.getTime() < 100) {
					Event.type = TOGGLE;
					Event.id = 0;
				}
				activeTimer[gameSettings::Left] = false;
				sentMove = false;
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Right]) {
				if (Timer.getTime() < 100) {
					Event.type = TOGGLE;
					Event.id = 0;
				}
				activeTimer[gameSettings::Right] = false;
				sentMove = false;
			}
			if (allegroEvent.keyboard.keycode == gameSettings::wormKeySet[gameSettings::Jump]) {
				//Nothing to do here
			}
		}
	}
	else {
		Event.type = NOEVENT;
		Event.id = 0;
	}

	return Event;
}

Event EventGenerator::transformNetworkEvent(void * nose)
{
	Event event;
	event.type = NOEVENT;

	return event;
}

void EventGenerator::checkIncomingEvents(AllegroTools * allegroTools, void * nose)
{
	pushEvent(transformAllegroEvent(allegroTools));
	//pushEvent(transformNetworkEvent(nose));
}

