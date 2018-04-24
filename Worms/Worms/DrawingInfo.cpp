#include "DrawingInfo.h"

using namespace std;

DrawingInfo::DrawingInfo()
{
	for (int i = 0; i < 15; i++)
		this->WormWalk[i] = NULL;
	for (int i = 0; i < 10; i++)
		this->WormJump[i] = NULL;
	this->Background = NULL;
	this->WindowsBackground = NULL;

}

DrawingInfo::~DrawingInfo()
{
	for (int i = 0; i < 15; i++) {
		al_destroy_bitmap(this->WormWalk[i]);
	}

	for (int i = 0; i < 10; i++) {
		al_destroy_bitmap(this->WormJump[i]);
	}

	al_destroy_bitmap(this->Background);
	al_destroy_bitmap(this->WindowsBackground);
}

void DrawingInfo::LoadWormImages() {
	string string;

	for (int i = 1; i < 16; i++) {
		string = str + to_string(i) + ng;    //Se inicializan los bitmaps de los worms
		this->WormWalk[i - 1] = al_load_bitmap(string.c_str());
	}

	for (int i = 1; i < 11; i++) {
		string = STR + to_string(i) + NG;
		this->WormJump[i - 1] = al_load_bitmap(string.c_str());
	}
}

void DrawingInfo::arrangeWormCycle()
{
	//Warmup
	for (int i = 0; i < 3; i++) {
		this->Wormcycle[i] = this->WormWalk[i];
	}
	//Primera fase
	for (int i = 3; i < 11; i++) {
		this->Wormcycle[i] = this->WormWalk[i];
	}
	this->Wormcycle[11] = this->WormWalk[10];
	for (int i = 12; i < 16; i++) {
		this->Wormcycle[i] = this->WormWalk[i-1];
	}
	this->Wormcycle[16] = this->WormWalk[3];
	//Segunda fase
	for (int i = 17; i < 25; i++) {
		this->Wormcycle[i] = this->WormWalk[i-14];
	}
	this->Wormcycle[24] = this->WormWalk[10];
	for (int i = 25; i < 30; i++) {
		this->Wormcycle[i] = this->WormWalk[i - 15];
	}
	this->Wormcycle[30] = this->WormWalk[3];
	//Tercera fase
	for (int i = 31; i < 39; i++) {
		this->Wormcycle[i] = this->WormWalk[i-28];
	}
	this->Wormcycle[39] = this->WormWalk[10];
	for (int i = 40; i < 44; i++) {
		this->Wormcycle[i] = this->WormWalk[i - 29];
	}
	this->Wormcycle[44] = this->WormWalk[3];
}