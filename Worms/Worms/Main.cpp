#include "Scenario.h"
#include "AllegroTools.h"
#include "Dispatcher.h"
#include "EventGenerator.h"
#include "GameSettings.h"
#include "Drawer.h"
#include "Sender.h"
#include "Network.h"
#include "Parser.h"

using namespace std;
int main(int argc, char* argv[]) {

	Parser Parser;

	Network Network(gameSettings::port);

	EventGenerator EventGenerator;
	Dispatcher Dispatcher;
	Event Event = { 0,0 };

	AllegroTools AllegroTools;
	Scenario Scene;
	Drawer Drawer;
	Sender Sender(&Network);

	srand(time(NULL));
	
	Scene.registerObserver(&Drawer);
	Scene.registerObserver(&Sender);

	Parser.Read(argc, argv);

	Network.loadOwnIP(Parser);
	Network.loadOtherIP();

	if (AllegroTools.Init()) {

		AllegroTools.drawingInfo.LoadWormImages();
		AllegroTools.drawingInfo.arrangeWormCycle();

		Network.setIfHost(AllegroTools.askIfHost()); //Bloqueante, pantalla con dos botones, un boton para ser host, uno para client. &0
		Network.acceptOrResolve(gameSettings::port);

		if (Network.getIfHost() != QUITTER) 
		{

			Scene.createNewWorm(0, { gameSettings::LeftWall + 200 , gameSettings::GroundLevel }, WormDirection::Right);

			if (Network.getIfHost() == HOST) {
				//drawwaitingforsomebody()
				Network.createLineServer();
			}
			else {
				//drawtryingtoconnect()
				Network.createLineClient(Network.getOtherIP(), gameSettings::port);
			}

			while (Event.type != QUIT && (Network.getIfHost() != gameSettings::QUITTER))
			{
				cout << "Network Protocol" << endl; //DEBUG
				Network.networkProtocol();

				cout << "Cheking Events" << endl; //DEBUG
				EventGenerator.checkIncomingEvents(&AllegroTools, &Network);

				for (int i = 0; i < 2; i++) {

					if (!(EventGenerator.eventQueue.empty())) {
						cout << "Fetching Events" << endl; //DEBUG
						Event = EventGenerator.fetchEvent();

						if (Event.type != NOEVENT) {
							cout << "Dispatching.." << endl; //DEBUG
							Dispatcher.Dispatch(Event, &Scene, &AllegroTools);
							cout << "Dispatched" << endl; //DEBUG
						}
						else {
							cout << "NOT DISPATCHED -- NOEVENT" << endl; //DEBUG
						}
					}
				}
			}
		}
	}
	return 0;
}