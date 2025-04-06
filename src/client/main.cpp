#include "../shared/olcGeoPixel.h"
#include "GameClient.h"
#include <SFML/Network.hpp>
//#include "Client.h"
#include "../shared/Settings.h"

int main()
{
	GameClient gameClient;

	if (gameClient.Construct(SCREENWIDTH, SCREENHEIGHT, PIXELSIZE, PIXELSIZE))
		gameClient.Start();

	return 0;
}