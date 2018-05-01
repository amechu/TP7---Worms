#pragma once

#include "Worm.h"
#include <stdint.h>
#include <string>
#include "GameSettings.h"
#include <cstdint>


#define ACKR_ (0x00)
#define ACK_ (0x01)
#define IAMRDY (0x02)
#define MOVE_ (0x03)
#define QUIT_	(0xFF)
#define ERROR_ (0xE0)

class Packet
{
public:
	Packet();
	~Packet();

	std::string makePacket(int8_t type, int16_t action=0, int32_t id=0, int16_t pos=0);
	std::string posToBigEndian(uint16_t pos);
	std::string idToBigEndian(uint32_t id);
	uint8_t header;
	uint8_t action;
	uint32_t id;
	uint16_t pos;

};

