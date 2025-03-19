#include "GameServer.h"

GameServer::GameServer()
{
	sAppName = "Server";
}

bool GameServer::OnUserCreate()
{
	server.listener.setBlocking(false);
	server.listener.listen(2000);

	return true;
}

bool GameServer::OnUserUpdate(float fElapsedTime)
{
	Draw(position);

	std::cout << position << "\n";

	server.update(this);

	return true;
}

