#include "../shared/olcPixelGameEngine.h"
#include "GameServer.h"
#include <SFML/Network.hpp>
#include "../shared/NetworkCommands.h"

int main()
{	
	GameServer gameServer;

	if (gameServer.Construct(SCREENWIDTH, SCREENHEIGHT, 2, 2))
		gameServer.Start();

	return 0;
}