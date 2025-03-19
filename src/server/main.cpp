#include "../shared/olcPixelGameEngine.h"
#include "Game.h"
#include <SFML/Network.hpp>
#include "../shared/NetworkCommands.h"

int main()
{	
	Game game;

	if (game.Construct(SCREENWIDTH, SCREENHEIGHT, 2, 2))
		game.Start();

	return 0;
}