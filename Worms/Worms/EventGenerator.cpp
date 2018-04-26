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
			Event.id = 0;
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

