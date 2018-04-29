#pragma once

#include <stdint.h>
#include <string>
#include "GameSettings.h"

class Packet
{
public:
	Packet();
	~Packet();

	std::string makePacket();
	std::string posToBigEndian(uint16_t pos);
	std::string idToBigEndian(uint32_t id);
	uint8_t header;
	uint8_t action;
	uint32_t id;
	uint16_t pos;

};

