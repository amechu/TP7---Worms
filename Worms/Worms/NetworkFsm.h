#pragma once
#include "Packet.h"
#include "Network.h"
#include "Timer.h"


enum networkEvent{ READY_RECEIVED, ACK_RECEIVED, MOVE_REQUEST_RECEIVED, NET_ERROR, QUIT_REQUEST_RECEIVED, TIMEOUT1, TIMEOUT2 };

enum networkState { READYTOCONNECT, WAIT_READY, WAIT_REQUEST, WAIT_ACK, SHUTDOWN };

typedef Packet(*pfun)(void* data, Network* network, NetworkFsm* netfsm);


#define N_EVENTS 7
#define N_STATES 4


typedef struct
{
	int nextState;
	pfun action;
}cell;



typedef struct 
{
	int LastEvent;
	int Event;
	bool leave;
	bool error;
	int timeouts = 0;
	bool quitall=false;

}data_t;


class NetworkFsm
{
public:
	NetworkFsm();
	~NetworkFsm();
	Packet listen(Network* network); // creo que se lo puede sacar VER
	void say(Packet packet, Network* network);
	Packet packet;
	Packet run(int ev, void * data, Network* network);	// el ev es el que llega del dispatcher y el data es la estructura donde se encuentran el evento anterior y el de ahora
	int getLastEvent();		//obtengo el ultimo evento que se ejecuto como para tener memoria de como hacerlo
	int getEvent();			//obtengo el evento que se va a ejecutar
	int getState();
	void setLastEvent(int lastev);
	void setEvent(int ev);
	Packet waitReady(Network* network);
	Packet waitRequest(Network* network);
	Packet waitAck(Network* network);
	data_t events;


private:

	const cell tabla[N_STATES][N_EVENTS] =
	{						//READY_RECEIVED			ACK_RECEIVED				MOVE_REQUEST_RECEIVED		NET_ERROR					QUIT_REQUEST_RECEIVED		TIMEOUT						TIMEOUT2
		{ /*READYTOCONNECT*/{WAIT_ACK,&sendReady},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{WAIT_REQUEST,&reSend},		{SHUTDOWN,&errorComm}},
		{ /*WAIT_READY*/    {WAIT_REQUEST,&sendAckr},	{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{WAIT_REQUEST,&reSend},		{SHUTDOWN,&errorComm}},
		{ /*WAIT_REQUEST*/	{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{WAIT_REQUEST,&sendAck},	{SHUTDOWN,&errorComm},		{SHUTDOWN,&sendAck},		{WAIT_REQUEST,&reSend},		{SHUTDOWN,&errorComm}},
		{ /*WAIT_ACK*/		{SHUTDOWN,&errorComm},		{WAIT_REQUEST,&rest},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{SHUTDOWN,&errorComm},		{WAIT_REQUEST,&reSend},		{SHUTDOWN,&errorComm}},
	};
	int estado;

};

//funciones que le corresponden a cada evento de la maquina de estados

Packet sendReady(void* data, Network* network, NetworkFsm* netfsm);
Packet sendAckr(void* data, Network* network, NetworkFsm* netfsm);
Packet rest(void* data, Network* network, NetworkFsm* netfsm);
Packet errorComm(void* data, Network* network, NetworkFsm* netfsm);
Packet sendAck(void* data, Network* network, NetworkFsm* netfsm);
Packet reSend(void* data, Network* network, NetworkFsm* netfsm);