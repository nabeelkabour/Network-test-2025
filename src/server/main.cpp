#define OLC_PGE_HEADLESS
#include "../shared/olcGeoPixel.h"
#include "GameServer.h"
#include <SFML/Network.hpp>
#include "../shared/NetworkCommands.h"
#include "../shared/Settings.h"

int main()
{	
	GameServer gameServer;

    if (gameServer.Construct(256, 240, 4, 4))
        gameServer.Start();

    return 0;
}