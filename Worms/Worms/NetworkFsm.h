#pragma once
#include "Packet.h"
#include "Network.h"
#include "Timer.h"


enum networkEvent{ SEND_READY, RECIEVE_READY, ACKS, SEND_MOVE_REQUEST, RECEIVED_MOVE_REQUEST, NET_ERROR, RECEIVED_QUIT_REQUEST, SEND_QUIT_REQUEST, TIMEOUT1, TIMEOUT2 };

enum networkState { READYTOCONNECT, WAIT_REQUEST, WAIT_ACK, SHUTDOWN };

typedef void(*pfun)(void* data, Network* network, NetworkFsm* netfsm);


#define N_EVENTS 10
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
	void say(Packet Packet);
	Packet listen(Network* network); // creo que se lo puede sacar VER
	Packet packet;
	void run(int ev, void * data);	// el ev es el que llega del dispatcher y el data es la estructura donde se encuentran el evento anterior y el de ahora
	int getLastEvent();		//obtengo el ultimo evento que se ejecuto como para tener memoria de como hacerlo
	int getEvent();			//obtengo el evento que se va a ejecutar
	int getState();
	void setLastEvent(int lastev);
	void setEvent(int ev);

	data_t events;


private:

	const cell tabla[N_STATES][N_EVENTS] =
	{						//SEND_READY						RECIEVE_READY					 ACK							  SEND_MOVE_REQUEST				RECEIVED_MOVE_REQUEST				NET_ERROR				 	   RECEIVED_QUIT_REQUEST			 SEND_QUIT_REQUEST						TIMEOUT									 TIMEOUT2
		{ /*READYTOCONNECT*/{READYTOCONNECT,&waitReadyConfirm},	{WAIT_REQUEST,&sendAck},		{SHUTDOWN,&errorComunication },	{SHUTDOWN,&errorComunication},	{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication }	,{READYTOCONNECT,&errorComunication }		,{SHUTDOWN,&errorComunication} },
		{ /*WAIT_REQUEST*/	{SHUTDOWN,&errorComunication},		{SHUTDOWN,&errorComunication},	{SHUTDOWN,&errorComunication},	{WAIT_ACK,&waitMoveConfirm},	{WAIT_REQUEST,&sendAck}			,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&sendAck}			,{WAIT_ACK,&quitAnswer}			,{SHUTDOWN,&errorComunication}				,{SHUTDOWN,&errorComunication} },
		{ /*WAIT_ACK*/		{SHUTDOWN,&errorComunication},		{SHUTDOWN,&errorComunication},	{WAIT_REQUEST,&AckRecieved },	{SHUTDOWN,&errorComunication} , {SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{WAIT_ACK,&reSend}							,{SHUTDOWN,&errorComunication} },
		{ /*SHUTDOWN*/		{SHUTDOWN,&doNothing},				{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}						,{SHUTDOWN,&errorComunication} },
	};
	int estado;
};

//funciones que le corresponden a cada evento de la maquina de estados

void waitReadyConfirm(void* data, Network* network, NetworkFsm* netfsm);

void errorComunication(void* data, Network* network);

void waitMoveConfirm(void* data, Network* network);

void quitAnswer(void* data, Network* network);	//

void sendAck(void* data, Network* network);

void AckRecieved(void* data, Network* network); //

void reSend(void* data, Network* network);

void doNothing(void* data, Network* network);