#include "Network.h"


Network::Network(std::string port)
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
}


Network::~Network()
{
	acceptor->close();
	socket->close();
	delete resolver;
	delete acceptor;
	delete socket;
	delete IO_handler;
}

void Network::networkProtocol()
{
	Packet Packet;
	Packet = listen(); //corre la fsm hasta que vuelva al estado inicial.
	pushToRecieved(Packet);
	if (!toSend.empty()) { //si hay algo para decir, lo manda
		Packet = fetchToSend();
		say(Packet);
	}
}

Packet Network::fetchToSend()
{
	Packet returnVal;
	returnVal.header = 0;
	
	if (!toSend.empty()) {
		returnVal = toSend.front();
		toSend.pop();
	}
	return returnVal;
}

Packet Network::fetchRecieved()
{
	Packet returnVal;
	returnVal.header = 0;

	if (!Recieved.empty()) {
		returnVal = Recieved.front();
		Recieved.pop();
	}

	return returnVal;
}

void Network::pushToSend(Packet packet)
{
	toSend.push(packet);
}

void Network::pushToRecieved(Packet packet)
{
	Recieved.push(packet);
}

void Network::createLineServer()
{
	acceptor->accept(*socket);
	socket->non_blocking(true);
}

void Network::createLineClient(std::string host, std::string port)
{
	try {

		endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(host, port));

		boost::asio::connect(*socket, endpoint);

		socket->non_blocking(true);
	}

	catch (std::exception & e) 
	{
		std::cout << "Error al intentar conectar" << std::endl;
		setIfHost(gameSettings::QUITTER);
	}
}

std::string Network::getInfoTimed(int limitInMs)
{
	Timer timer;
	char buffer[6];
	size_t lenght = 0;
	boost::system::error_code error;

	timer.start();

	bool timeout = false;

	do 
	{
		lenght = this->socket->read_some(boost::asio::buffer(buffer), error);
		timer.stop();

		if (timer.getTime() > limitInMs && lenght == 0) 
		{														// Pido que lenght == 0 asi no lo paro mientras esta mandando
			timeout = true;
		}

	} while (error && !timeout);

	std::string retValue;

	if (!timeout) 
	{
		buffer[lenght] = 0;
		retValue = buffer;
	}
	else
		retValue = TIMEOUT;

	return retValue;
}

void Network::sendInfo(std::string msg)
{																//&0 hacer  que funque con server y no client
	size_t lenght = 0;
	boost::system::error_code error;

	do {

		lenght = this->socket->write_some(boost::asio::buffer(msg, msg.size()), error);

	} while (error);

}

void Network::acceptOrResolve(std::string port)
{
	if (getIfHost() == gameSettings::HOST)
	{
		acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
	}
	else
	{
		resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	}
}

using namespace std;

Packet Network::listen()
{
	Packet Packet;
	std::string string;
	bool check = false, good = false;

	do {
		if (estado == READYTOCONNECT) {
			if (getIfHost()) {
				sendInfo(Packet.makePacket(IAMRDY, 0, 0, gameSettings::WormInitialPosition));
				this->estado = WAIT_READY;
				Packet = waitReady();
				if (Packet.header == IAMRDY) {
					run(READY_RECEIVED);
				}
				else {
					run(NET_ERROR);
				}
			}
			else {
				Packet = waitReady();
				if (Packet.header == IAMRDY) {
					run(READY_RECEIVED);
				}
				else {
					run(NET_ERROR);
				}
			}
		}
		else if (estado == WAIT_REQUEST) {

			Packet = waitRequest();

		}
		else if (estado == WAIT_ACK) {

			Packet = waitAck();

		}
	} while (estado != WAIT_REQUEST);

	return Packet;
}

void Network::say(Packet packet)
{
	estado = WAIT_ACK;
	sendInfo(packet.makePacket(packet.header, packet.action, packet.id, packet.pos));
	if (packet.header == QUIT_) {
		setLastEvent(QUIT_REQUEST_RECEIVED);
	}

}

Packet Network::run(int ev)
{
	Packet packet;

	setLastEvent(ev);

	if (ev == TIMEOUT1) {
		estado = WAIT_REQUEST;
		packet = reSend();
	}

	switch (estado) {
	case READYTOCONNECT:
		switch (ev) {
		case READY_RECEIVED:
			estado = WAIT_ACK;
			packet = sendReady();
			break;
		default:
			estado = SHUTDOWN;
			packet = errorComm();
		}
		break;
	case WAIT_READY:
		switch (ev) {
		case READY_RECEIVED:
			packet = sendAckr();
			break;
		default:
			estado = SHUTDOWN;
			packet = errorComm();
		}
		break;
	case WAIT_REQUEST:
		switch (ev) {
		case MOVE_REQUEST_RECEIVED:
			estado = WAIT_REQUEST;
			packet = sendAck();
			break;
		}
	default:
		estado = SHUTDOWN;
		packet = errorComm();
		break;
	case WAIT_ACK:
		switch (ev) {
		case ACK_RECEIVED:
			estado = WAIT_REQUEST;
			packet = rest();
			break;
		default:
			estado = SHUTDOWN;
			packet = errorComm();
		}
		break;
	}

	return packet;
};

Packet Network::waitReady() {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(IAMRDY)) {
				good = true;
				aux += (string.c_str())[2];
				aux += (string.c_str())[1];
				pos = stoi(aux);
				Packet.header = IAMRDY;
				Packet.pos = pos;
			}
			else {
				run(NET_ERROR);
				Packet.header = ERROR_;
			}
		}
		else
			i++;
	}
	if (!good) {
		run(TIMEOUT2);
		Packet.header = ERROR_;
	}

	return Packet;
}

Packet Network::waitRequest() {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(MOVE_)) {
				good = true;
				aux += (string.c_str())[5];
				aux += (string.c_str())[4];
				aux += (string.c_str())[3];
				aux += (string.c_str())[2];
				this->packet.header = MOVE_;
				this->packet.action = (string.c_str())[1];
				this->packet.id = stoi(aux);
				run(MOVE_REQUEST_RECEIVED);
				Packet = this->packet;
			}
			else if ((string.c_str())[0] == (char)(IAMRDY) || (string.c_str())[0] == (char)(ACK_) || (string.c_str())[0] == (char)(ERROR_)) {
				good = true;
				Packet = run(NET_ERROR);
			}
			else if ((string.c_str())[0] == (char)(QUIT_)) {
				Packet = run(QUIT_REQUEST_RECEIVED);
			}
		}
		else
			i++;
	}
	if (!good) {
		Packet.header = 0;
	}

	return Packet;
}

Packet Network::waitAck() {

	int i = 0, pos = 0;
	bool check = false, good = false;
	std::string string, aux;
	Packet Packet;
	Packet.header = 0;

	while (i < 5 || !check) {
		string = getInfoTimed(20);
		if (string != "timeout") {
			check = true;
			if ((string.c_str())[0] == (char)(ACK_)) {
				good = true;
				aux += (string.c_str())[4];
				aux += (string.c_str())[3];
				aux += (string.c_str())[2];
				aux += (string.c_str())[1];
				if (getLastEvent() == READY_RECEIVED) {
					if (!(stoi(aux) == 0)) {
						run(NET_ERROR);
					}
					else {
						Packet.header = ACK_;
						Packet.id = 0;
					}
				}
				else if (getLastEvent() == QUIT_REQUEST_RECEIVED) {
					if (!(stoi(aux) == 0)) {
						run(NET_ERROR);
					}
					else {
						Packet.header = QUIT_;
						Packet.id = 0;
					}
				}
				else {
					if (stoi(aux) == this->packet.id) {
						run(ACK_RECEIVED);
					}
				}
			}
			else {
				good = true;
				Packet = run(NET_ERROR);
			}
		}
		else
			i++;
	}
	if (!good) {
		Packet.header = 0;
	}

	return Packet;
}

void Network::loadOwnIP(Parser& Parser) {
	this->myIP = Parser.myIP;
}

void Network::loadOtherIP() {
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

////////////////////////////Setters & Getters////////////////////////////////////

int Network::getLastEvent()
{
	return lastEvent;
}

Packet Network::getPacket()
{
	return packet;
}

void Network::setLastEvent(int ev)
{
	lastEvent = ev;
}

int Network::getState()
{
	return estado;
}

void Network::setIfHost(int imhost) {
	this->iAmHost = imhost;
}

std::string Network::getOwnIP() {
	return this->myIP;
}

std::string Network::getOtherIP()
{
	return this->OtherIP;
}

int Network::getIfHost()
{
	return this->iAmHost;
}

Packet Network::sendReady()
{
	Packet packet;
	packet.header = 0;
	sendInfo(packet.makePacket(IAMRDY, 0, 0, gameSettings::WormInitialPosition + 400));
	return packet;
}

Packet Network::sendAckr()
{
	Packet packet;
	packet.header = 0;
	sendInfo(packet.makePacket(ACK_, 0, 0, 0));
	return packet;
}

Packet Network::rest()
{
	Packet packet;
	packet.header = 0;
	return packet;
}

Packet Network::errorComm()
{
	Packet packet;
	packet.header = ERROR_;
	return packet;
}

Packet Network::sendAck()
{
	Packet packet;
	packet.header = 0;
	if (getLastEvent() == MOVE_REQUEST_RECEIVED) {
		sendInfo(packet.makePacket(ACK_, 0, (getPacket()).id, 0));
	}
	else if (getLastEvent() == QUIT_REQUEST_RECEIVED) {
		sendInfo(packet.makePacket(ACK_, 0, 0, 0));
		packet.header = QUIT_;
	}
	return packet;
}

Packet Network::reSend()
{
	Packet packet;
	packet.header = 0;
	return packet; //pensar
}
