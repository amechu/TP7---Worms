#pragma once
#include "Packet.h"


enum networkEvent{ SEND_READY, RECIEVE_READY, ACK, SEND_MOVE_REQUEST, RECEIVED_MOVE_REQUEST, NET_ERROR, RECEIVED_QUIT_REQUEST, SEND_QUIT_REQUEST, TIMEOUT1, TIMEOUT2 };

enum networkState { READYTOCONNECT, WAIT_REQUEST, WAIT_ACK, SHUTDOWN };

typedef void(*pfun)(void* data);


#define N_EVENTS 10
#define N_STATES 4


typedef struct
{
	int nextState;
	pfun action;
}cell;



//funciones que le corresponden a cada evento de la maquina de estados

void waitReadyConfirm(void* data);

void errorComunication(void* data);

void waitMoveConfirm(void* data);

void quitAnswer(void* data);

void sendAck(void* data);

void doStuff(void* data);

void reSend(void* data);

void doNothing(void* data);




class NetworkFsm
{
public:
	NetworkFsm();
	~NetworkFsm();
	void say(Packet Packet);
	Packet listen();

private:

	const cell tabla[N_STATES][N_EVENTS] =
	{						//SEND_READY						RECIEVE_READY					 ACK							  SEND_MOVE_REQUEST				RECEIVED_MOVE_REQUEST				NET_ERROR				 	   RECEIVED_QUIT_REQUEST			 SEND_QUIT_REQUEST						TIMEOUT									 TIMEOUT2
		{ /*READYTOCONNECT*/{READYTOCONNECT,&waitReadyConfirm},	{WAIT_REQUEST,&sendAck},		{SHUTDOWN,&errorComunication },	{SHUTDOWN,&errorComunication},	{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication }	,{READYTOCONNECT,&errorComunication }		,{SHUTDOWN,&errorComunication} },
		{ /*WAIT_REQUEST*/	{SHUTDOWN,&errorComunication},		{SHUTDOWN,&errorComunication},	{SHUTDOWN,&errorComunication},	{WAIT_ACK,&waitMoveConfirm},	{WAIT_REQUEST,&sendAck}			,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&sendAck}			,{WAIT_ACK,&quitAnswer}			,{SHUTDOWN,&errorComunication}				,{SHUTDOWN,&errorComunication} },
		{ /*WAIT_ACK*/		{SHUTDOWN,&errorComunication},		{SHUTDOWN,&errorComunication},	{WAIT_REQUEST,&doStuff},		{SHUTDOWN,&errorComunication} , {SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{SHUTDOWN,&errorComunication}	,{WAIT_ACK,&reSend}							,{SHUTDOWN,&errorComunication} },
		{ /*SHUTDOWN*/		{SHUTDOWN,&doNothing},				{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing},			{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}			,{SHUTDOWN,&doNothing}						,{SHUTDOWN,&errorComunication} },
	};
	int estado;

};

