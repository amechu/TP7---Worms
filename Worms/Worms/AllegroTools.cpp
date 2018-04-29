#include "AllegroTools.h"
#include "GameSettings.h"
#include <iostream>


AllegroTools::AllegroTools()
{
	this->Timer = NULL;
	this->Queue = NULL;
	this->Display = NULL;
	this->Font = NULL;
}


AllegroTools::~AllegroTools()
{
	al_destroy_display(this->Display);
	al_destroy_timer(this->Timer);
	al_destroy_event_queue(this->Queue);
	al_destroy_font(this->Font);
}

bool AllegroTools::Init() {

	bool ret = false;

	if (al_init()) {
		if (al_init_font_addon()) {
			if (al_init_primitives_addon()) {
				if (al_init_image_addon()) {
					if (al_install_keyboard()) {
						if (this->Display = al_create_display(gameSettings::SCREEN_W, gameSettings::SCREEN_H)) {
							if (this->Timer = al_create_timer(1 / gameSettings::FPS)) {
								if ((drawingInfo.Background = al_create_bitmap(gameSettings::SCREEN_W, gameSettings::SCREEN_H)) && (drawingInfo.WindowsBackground = al_create_bitmap(gameSettings::SCREEN_W, gameSettings::SCREEN_H))) {
									if (this->Queue = al_create_event_queue()) {
										if ((drawingInfo.Background = al_load_bitmap("Scenario.png")) && (drawingInfo.WindowsBackground = al_load_bitmap("stars.png"))) {
											if (this->Font = al_load_font("montserrat.ttf", 20, 0)) {
												ret = true;
											}
											else {
												ret = false;
												al_destroy_display(this->Display);
												al_destroy_timer(this->Timer);
												al_destroy_bitmap(drawingInfo.Background);
												al_destroy_event_queue(this->Queue);
												al_destroy_bitmap(drawingInfo.WindowsBackground);
											}
										}

										else {
											ret = false;
											al_destroy_display(this->Display);
											al_destroy_timer(this->Timer);
											al_destroy_bitmap(drawingInfo.Background);
											al_destroy_bitmap(drawingInfo.WindowsBackground);
											al_destroy_event_queue(this->Queue);
										}
									}
									else {
										al_destroy_display(this->Display);
										al_destroy_timer(this->Timer);
										al_destroy_bitmap(drawingInfo.Background);
									}
								}
								else {
									ret = false;
									al_destroy_display(this->Display);
									al_destroy_timer(this->Timer);
								}
							}
							else {
								ret = false;
								al_destroy_display(this->Display);
							}
						}
						else
							ret = false;
					}
					else
						ret = false;
				}
				else
					ret = false;
			}
			else
				ret = false;
		}
		else
			ret = false;
	}

	for (int i = 0; i < 15; i++) {
		if (drawingInfo.WormWalk[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	for (int i = 0; i < 10; i++) {
		if (drawingInfo.WormJump[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	if (ret) {
		al_register_event_source(this->Queue, al_get_display_event_source(this->Display));
		al_register_event_source(this->Queue, al_get_timer_event_source(this->Timer));
		al_register_event_source(this->Queue, al_get_keyboard_event_source());

		al_start_timer(this->Timer);
	}
	else {
		for (int i = 0; i < 15; i++) {
			al_destroy_bitmap(drawingInfo.WormWalk[i]);
		}
		for (int i = 0; i < 10; i++) {
			al_destroy_bitmap(drawingInfo.WormJump[i]);
		}
	} 

	return ret;
}

using namespace gameSettings;
bool AllegroTools::askIfHost()
{
	ALLEGRO_BITMAP* buttonHost = al_create_bitmap(3*SCREEN_W/10+6, 1*SCREEN_H/10+6);
	ALLEGRO_BITMAP* buttonConnect = al_create_bitmap(3 * SCREEN_W / 10 + 6, 1 * SCREEN_H / 10 + 6);
	ALLEGRO_BITMAP* buttonQuit = al_create_bitmap(2 * SCREEN_W / 10 + 6, 1 * SCREEN_H / 10 + 6);

	ALLEGRO_BITMAP* disp = al_get_target_bitmap();

	al_set_target_bitmap(buttonHost);
	al_draw_rectangle(0, 0, 3 * SCREEN_W/10+3, 1*SCREEN_H/10+3 , al_map_rgb(0, 40, 40), 3);
	al_draw_filled_rectangle(3, 3, 3 * SCREEN_W / 10, 1 * SCREEN_H / 10, al_map_rgb(100, 40, 40));
	al_draw_text(this->Font, al_map_rgb(0, 40, 40), (3*SCREEN_W/10 + 6)/2, (1*SCREEN_H/10+6)/2, ALLEGRO_ALIGN_CENTER, "Host party");

	al_set_target_bitmap(buttonConnect);
	al_draw_rectangle(0, 0, 3 * SCREEN_W / 10+3, 1 * SCREEN_H / 10+3, al_map_rgb(0, 40, 40), 3);
	al_draw_filled_rectangle(3, 3, 3 * SCREEN_W / 10, 1 * SCREEN_H / 10, al_map_rgb(100, 40, 40));
	al_draw_text(this->Font, al_map_rgb(0, 40, 40), (3 * SCREEN_W / 10 + 6) / 2, (1 * SCREEN_H / 10 + 6) / 2, ALLEGRO_ALIGN_CENTER, "Connect to party");

	al_set_target_bitmap(buttonQuit);
	al_draw_rectangle(0, 0, 2*SCREEN_W/10+3, 1 * SCREEN_H / 10 + 3, al_map_rgb(0, 40, 40), 3);
	al_draw_filled_rectangle(3, 3, 2*SCREEN_W/10, 1*SCREEN_H/10, al_map_rgb(100, 40, 40));
	al_draw_text(this->Font, al_map_rgb(0, 40, 40), (2*SCREEN_W/10+6) / 2, (1 * SCREEN_H / 10 + 6) / 2, ALLEGRO_ALIGN_CENTER, "Quit");

	al_set_target_bitmap(disp);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(buttonHost, , , NULL);
	al_draw_bitmap(buttonConnect, , , NULL);
	al_draw_bitmap(buttonQuit, , , NULL);
	al_flip_display();


	/*codigo para saber cual eligio*/



	getchar();

	return false;
}
