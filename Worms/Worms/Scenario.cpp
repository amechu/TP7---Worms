#include "Scenario.h"


Scenario::Scenario()
{
}


Scenario::~Scenario()
{
}

void Scenario::createNewWorm(unsigned int id, Point position, WormDirection direction)
{
	Worm* worm = new Worm(id, position, direction);
	this->Worms.push_back(*worm);
}

void Scenario::destroyWorm(unsigned int id)
{
	for (std::vector<Worm>::iterator it = Worms.begin(); it != Worms.end(); it++) {
		if ((*it).getId() == id)
			Worms.erase(it);
	}
}

std::vector<Worm> Scenario::getWormList()
{ 
	return (this->Worms);
}

void Scenario::moveLeft(Event event, AllegroTools* allegroTools)
{
	for (Worm& worm : this->Worms) {
		if (worm.getId() == event.id) {
			worm.moveLeft(EVENT_DRIVEN); 
		}
	}
	this->lastAction.id = LEFT;
	this->lastAction.origin = (event.id == 0 ? LOCAL : EXTERNAL);
	this->notify(allegroTools);
}

void Scenario::moveRight(Event event, AllegroTools* allegroTools)
{
	for (Worm& worm : this->Worms) {
		if (worm.getId() == event.id) {
			worm.moveRight(EVENT_DRIVEN);
		}
	}
	this->lastAction.id = RIGHT;
	this->lastAction.origin = (event.id == 0 ? LOCAL : EXTERNAL);
	this->notify(allegroTools);
}

void Scenario::Jump(Event event, AllegroTools* allegroTools)
{
	for (Worm& worm : this->Worms) {
		if (worm.getId() == event.id) {
			worm.jump();
		}
	}
	this->lastAction.id = JUMP;
	this->lastAction.origin = (event.id == 0 ? LOCAL : EXTERNAL);
	this->notify(allegroTools);
}

void Scenario::Toggle(Event event, AllegroTools* allegroTools)
{
	for (Worm& worm : this->Worms) {
		if (worm.getId() == event.id) {
			worm.toggle();
		}
	}
	this->lastAction.id = TOGGLE;
	this->lastAction.origin = (event.id == 0 ? LOCAL : EXTERNAL);
	this->notify(allegroTools);
}

void Scenario::Refresh(AllegroTools* allegroTools)
{
	for (Worm& worm : this->Worms) {
		worm.refresh();
	}
	this->lastAction.id = REFRESH;
	this->notify(allegroTools);
}
