#pragma once
#include <vector>
#include "Subject.h"
#include "EventHandling.h"
#include "AllegroTools.h"
#include "Worm.h"

enum ACTION_ORIGIN {EXTERNAL, LOCAL};

class Scenario : public Subject
{
public:
	Scenario();
	~Scenario();

	void createNewWorm(unsigned int id, Point position, WormDirection direction);
	void destroyWorm(unsigned int id);

	void moveLeft(Event event, AllegroTools* allegroTools);
	void moveRight(Event event, AllegroTools* allegroTools);
	void Jump(Event event, AllegroTools* allegroTools);
	void Toggle(Event event, AllegroTools* allegroTools);
	void Refresh(AllegroTools* allegroTools, bool callFromRefresh);
	void directWorm(Event event, WormDirection dir);
	void setWormState(Event event, WormState state);

	std::vector<Worm> getWormList();



private:
	//Por herencia, notify();
	std::vector<Worm> Worms;
	unsigned int wormCount = 0;
};