#include "../shared/olcPixelGameEngine.h"
#include "GameClient.h"
#include <SFML/Network.hpp>
#include "Client.h"

int main()
{
	GameClient gameClient;

	if (gameClient.Construct(SCREENWIDTH, SCREENHEIGHT, 2, 2))
		gameClient.Start();

	return 0;
}