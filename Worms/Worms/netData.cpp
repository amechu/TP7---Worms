#include "netData.h"

void netData::loadOwnIP(Parser& Parser) {
	this->myIP = Parser.myIP;
}

void netData::loadOtherIP() {
	std::ifstream dirFile;
	dirFile.open(IPFILE); //Abrimos el archivo .txt con las direcciones IP...

	std::string auxString; //...Y creamos un string auxiliar para poder trabajarlas.

	while (dirFile.good()) { // ¿Aún hay direcciones que agarrar?
		getline(dirFile, auxString); //Si las hay, la ponemos en el string auxiliar...
		if (auxString != this->myIP) {
			this->OtherIP = auxString;
		}
	}
}

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
