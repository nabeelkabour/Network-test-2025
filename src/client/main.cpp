#include "../shared/olcPixelGameEngine.h"
#include "Game.h"
#include <SFML/Network.hpp>
#include "Client.h"

int main()
{
	if (game.Construct(SCREENWIDTH, SCREENHEIGHT, 2, 2))
		game.Start();

	return 0;
}