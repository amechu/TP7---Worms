#pragma once
#include "Observer.h"
#include "Packager.h"
#include <string>

class Sender : public Observer
{
public:
	Sender();
	~Sender();
	void update(void* subject, void* tool); //&0
	void send(std::string package); //&0

};

