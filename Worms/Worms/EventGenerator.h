#pragma once
#include "AllegroTools.h"
#include "EventHandling.h"
#include "Timer.h"
#include <queue>
#include "GameSettings.h"


class EventGenerator
{
public:
	EventGenerator();
	~EventGenerator();
	void pushEvent(Event event);
	Event fetchEvent();
	Event transformAllegroEvent(AllegroTools* allegroTools);
	Event transformNetworkEvent(void* nose); //Recibe el paquete crudo de network y lo convierte a Event. Pensar si esta funcion esta bien aca. &0
	void checkIncomingEvents(AllegroTools* allegroTools, void* nose);


public:
	bool activeEvents[gameSettings::TotalActions] = { 0 };
	bool activeTimer[gameSettings::TotalActions - 1] = { 0 }; //No es necesario un timer para jump
	std::queue<Event> eventQueue;
	Timer Timer;
	bool isTimerActive = false;
	bool sentMove = false;
};

