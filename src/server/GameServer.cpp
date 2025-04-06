#include "GameServer.h"
#include "../shared/Resources.h"
#include "ZombieServer.h"

GameServer::GameServer()
{
	sAppName = "Server";
}

bool GameServer::OnUserCreate()
{
	server.listener.setBlocking(false);
	server.listener.listen(2000);

	Resources::get();

	while (server.clients.size() < 2)
	{
		server.update(this);
	}

	return true;
}

bool GameServer::OnUserUpdate(float fElapsedTime)
{
	server.update(this);
	zombieSpawner.loop(this);

	
	for (ObjectServer* o : instanceList)
	{
		o->loop(this);
	}

	zombieList.remove_if([&](const ZombieServer* z) { return z->Basic::removeFlag; });

	instanceList.remove_if([&](const ObjectServer* o)
		{
			if (o->removeFlag)
			{
				delete o;
				return true;
			}
			else
			{
				return false;
			}
		});

	return true;
}