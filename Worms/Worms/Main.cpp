#include "Scenario.h"
#include "AllegroTools.h"
#include "Dispatcher.h"
#include "EventGenerator.h"
#include "GameSettings.h"
#include "Drawer.h"
#include "Sender.h"
#include "Network.h"
#include "Parser.h"

//Buscar "&0" en solucion para ver lo que falta hacer
//Falta: Todo lo de networking, desde mandar paquetes hasta armarlos hasta ver que hacer con el evento quit, o crear worm nuevo a partir de una coneccion.
//Considerar: los eventos en EventHandling.h que son refresh+algo son para el worm local y generados por allegro, los que son solo algo son para todos
//los demas worms de networking.
int main(int argc, char* argv[]) {

	Parser Parser;

	Client client;
	Server server(gameSettings::port);
	Network Network(&client, &server);

	EventGenerator EventGenerator;
	Dispatcher Dispatcher;
	Event Event = { 0,0 };

	AllegroTools AllegroTools;

	Scenario Scene;
	Drawer Drawer;
	Sender Sender;

	Scene.registerObserver(&Drawer);
	Scene.registerObserver(&Sender);

	Parser.Read(argc, argv);

	Network.netData.loadOwnIP(Parser);
	Network.netData.loadOtherIP();

	if (AllegroTools.Init()) {

		AllegroTools.drawingInfo.LoadWormImages();
		AllegroTools.drawingInfo.arrangeWormCycle();

		Network.netData.setIfHost(AllegroTools.askIfHost()); //Bloqueante, pantalla con dos botones, un boton para ser host, uno para client. &0

		if (Network.netData.getIfHost() != QUITTER) {

			

			Scene.createNewWorm(0, { gameSettings::LeftWall + 200 , gameSettings::GroundLevel }, WormDirection::Right);

			/*	if (Network.netData.getIfHost() == HOST) {
			AllegroTools.drawWaitingToConnect(); //Pone pantalla que dice que estas esperando a que alguien se te conecte. &0
			Network.Server->listen();
			}
			else {
			AllegroTools.drawTryingToConnect();
			Network.Client->connect(Network.netData.getOtherIP(), gameSettings::port);
			}
			*/
			while (Event.type != QUIT) {

				if (Network.netData.getIfHost() == HOST)
					server.createLineServer();

				else
					client.createLineClient(Network.netData.getOwnIP(), gameSettings::port);

				EventGenerator.checkIncomingEvents(&AllegroTools, &Network);

				if (!(EventGenerator.eventQueue.empty())) {

					Event = EventGenerator.fetchEvent();

					if (Event.type != NOEVENT)

						for (int i = 0; i < 2; i++) {
							Dispatcher.Dispatch(Event, &Scene, &AllegroTools);
						}
				}
			}
		}
	}
	return 0;
}































/*

Se utiliza la misma FSM del otro TP pero ahora hay que implementarla con un contenido.

Model View Controller (MVC) //Mirar

Como empezariamos este TP?

Event Generator, Clase evento? (ya la tengo hecha)

class Scenario
{
public:
	createNewWorm(ulong id = 0, point pos = {?, ?}, direction dir = left);
	destroyWorm(ulong id);
	addObserver(Observer* obs);
	moveLeft(eventtype ev);
	moveRight(eventtype ev);
	Jump(eventtype ev);
	Toggle(eventtype ev);
	Refresh(eventtype ev);
	Inactive(eventtype ev);

private:
	list<worm> w;
	list<observer*> obs;
	void update(void);
	ImgFondo;
}

Void Sceneraio::update(void){
	List<Observer*>::Iterator it;

	For(it = obs.begin(); it != obs.end(); it++)  //++ sobrecargado para pasar al proximo item de lista
		(*it) -> update(this);

}

class Observer {
	virtual void update(void* data) = 0;
};

class drawScenario : public Observer {
	public:
	drawScenario(ALLEGRO_BITMAP wallpaper, ALLEGRO_DISPLAY disp, etc);
	void update(void* data);
	
	private:
	drawWorm();
	ALLEGRO_BITMAP wallpaper;
	etc;
};

void drawScenario::update(void* data) {
	Scenario* S = (Scenario*) data;
	al_draw_bitmap(wallpaper);
	List<worm>* wl = S -> getWormList();
	List<worm>::iterator it;
	for(it = wl->begin(); it = wl->end(); it++)
		drawWorm(it->getPos());
	al_flip_display();
};

void Scenario::refresh(eventtype* ev){
	List<Worm>::iterator it;
	for(it = w.begin(); it != w.end(); it++)
		W -> refresh();
	lastAction = REFRESH;
	update(); //llama a todos los observers que van a ver que hubo un refresh como lastaction.
};

void Scenario::moveLeft(eventtype* ev){
	List<worm>::iterator it;
	for(it = w.begin(); it != w.end(); it++)
		if(w->getId() == ev->getId())
			w->StartWaking(); //Busca que gusano tiene que empezar a moverse
	lastAction = LEFT;
	update();
};

class SendMovement : public Observer {
public:
	void update(void* data);
	sendMovement(?);
private:
(...)
};

int main (int argc, char* argv[]){
	Scenario S;
	drawScenario d;
	sendMovement sm;
	S.addObserver(&a);
	S.addObserver(&sm);
	quit = false;

	while(!quit) {
		if(evg.hayEvento()) {
			dispatch(evg.getEvento(), &S);
			quit = evg.isQuit();
		}
	}
	destroyAllegro();
	return 0;

}

bool eventGen::hayEvento() {  //List<eventtype*> ev que esta adentro de evg.
	if(hayEventosAllegro()) //agarra y mira la eventqueue de allegro
		ev.push_back(getAllegroEvent())
	if(hayEventosNetworking()) //lee readsum de boost a ver si llego un paquete
		ev.push_back(getNetworkingEvent())//traduce paquete y manda un moveleft, jump, etc
	if(ev.size() > 0)
		return true;
	else
		return false;
};



*/