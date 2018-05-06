#pragma once

#include "Worm.h"
#include <stdint.h>
#include <string>
#include "GameSettings.h"
#include <cstdint>


#define ACK_ (0x01)
#define IAMRDY (0x20)
#define MOVE_ (0x30)
#define QUIT_	(0xFF)
#define ERROR_ (0xE0)

#define ACTIONRIGHT ('D')
#define ACTIONLEFT ('L')
#define ACTIONJUMP ('J')
#define ACTIONTOGGLE ('T')

class Packet
{
public:
	Packet();
	~Packet();

	std::string makePacket(uint8_t type, int16_t action=0, int32_t id=0, int16_t pos=0);
	std::string posToBigEndian(int16_t* pos);
	std::string idToBigEndian(int32_t* id);
	uint8_t header;
	int8_t action;
	int32_t id;
	int16_t pos;

};

