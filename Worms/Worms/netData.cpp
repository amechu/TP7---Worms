#include "netData.h"

//-----------------SETTERS-------------------//

void netData::setIfHost(bool imhost) {
	this->iAmHost = imhost;
}

//----------------GETTERS-------------------//
std::string netData::getOwnIP() {
	return this->myIP;
}

std::string netData::getOtherIP()
{
	return this->OtherIP;
}

bool netData::getIfHost()
{
	return this->iAmHost;
}
