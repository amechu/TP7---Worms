#pragma once
#include "Packet.h"
class NetworkFsm
{
public:
	NetworkFsm();
	~NetworkFsm();
	void say(Packet Packet);
	Packet listen();
};

