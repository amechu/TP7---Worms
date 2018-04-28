#pragma once
#include "DrawingInfo.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

class AllegroTools
{
public:
	AllegroTools();
	~AllegroTools();

	bool Init();
	bool askIfHost();

	DrawingInfo drawingInfo;
	ALLEGRO_TIMER * Timer;
	ALLEGRO_EVENT_QUEUE* Queue;
	ALLEGRO_DISPLAY* Display;
};

