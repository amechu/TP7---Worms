#pragma once

#include "Parser.h"

#include <string>
#include <vector>
#include <fstream>

class netData {
public:

		void loadOwnIP(Parser& Parser);//se fija que ip te pasaron por parser. &0
		void loadOtherIP();//Se fija cual de las dos ips en el .txt no es la que me pasaron por parser y la devuelvo. &0

		//------Setters------//
		void setOwnIP(unsigned int i);
		void setIfHost(int imhost);

		//------Getters------//
		std::string getOwnIP(); 
		std::string getOtherIP(); 
		int getIfHost(); //Devuelve el modo actual de la maquina (Cliente o server)

private:
		std::string myIP; //La direccion IP de la computadora actual.
		std::string OtherIP;

		int iAmHost;
		const std::string IPFILE = "DireccionesIP.txt";

};