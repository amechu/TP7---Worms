#pragma once

#include <string>
#include <vector>
#include <fstream>

class netData {
public:
		netData() {

			loadIPs();

		}

		//------Setters------//
		void setOwnIP(unsigned int i);
		void setIfHost(bool imhost);

		//------Getters------//

		std::string getOwnIP();
		unsigned int getIPListSize(); //Devuelve el tama�o del vector.
		const char * getIPAt(int i); //Devuelve la IP en una posici�n dada del vector.
		bool getIfHost(); //Devuelve el modo actual de la maquina (Cliente o server)

private:
		std::string myIP; //La direccion IP de la computadora actual.
		std::vector<std::string> IPList; //La lista de IPs de todas las m�quinas involucrada.

		bool iAmHost;
		void loadIPs();
		const std::string IPFILE = "DireccionesIP.txt";

};