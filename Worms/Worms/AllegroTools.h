#pragma once
#include "DrawingInfo.h"
#include <allegro5\allegro.h>

class AllegroTools
{
public:
	AllegroTools();
	~AllegroTools();

	bool Init();

	DrawingInfo drawingInfo;
	ALLEGRO_TIMER * Timer;
	ALLEGRO_EVENT_QUEUE* Queue;
	ALLEGRO_DISPLAY* Display;
};

