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

	std::queue<Event> eventQueue;


private:
	bool activeTimer[gameSettings::TotalActions] = { 0 }; 
	Timer Timer;
	bool sentMove = false;
	bool firstMove = true;
};

