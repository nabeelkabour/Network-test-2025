#include "Game.h"

Game game;

Game::Game()
{
	sAppName = "Server";
}

bool Game::OnUserCreate()
{
	server.listener.setBlocking(false);
	server.listener.listen(2000);

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	Draw(position);

	std::cout << position << "\n";

	server.update(this);

	return true;
}

