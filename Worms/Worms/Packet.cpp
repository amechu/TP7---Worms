#include "Packet.h"



Packet::Packet()
{
}


Packet::~Packet()
{
}
using namespace gameSettings;
std::string Packet::makePacket(int8_t header, int16_t action , int32_t id , int16_t pos )
{
	std::string string;

	switch (header) {
	case QUITPACKET:
		string = QUIT_;
		break;
	case ERRORNET:
		string = ERROR_;
		break;
	case I_AM_READY:
		string = IAMRDY;
		string += (posToBigEndian(pos));	
		break;
	case ACK:
		string = ACK_;
		string += (idToBigEndian(id));
		break;
	case MOVE:
		string = MOVE_;
		string += action;
		string += (idToBigEndian(id));
		break;
	}


	return string;
}

std::string Packet::posToBigEndian(uint16_t pos)
{
	std::string string;
	uint8_t* pospointer = (uint8_t*)pos;

	for (int i = 1; i = 0; i--) {
		string += pospointer[i];
	}
	return string;
}

std::string Packet::idToBigEndian(uint32_t id)
{
	std::string string;
	uint8_t* pospointer = (uint8_t*)pos;

	for (int i = 3; i = 0; i--) {
		string += pospointer[i];
	}
	return string;
}
