#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Networking.h"
#include "../shared/GameMechanics/Zombie.h"
#include "ZombieSpawner.h"
#include "ObjectServer.h"

class GameServer : public olc::PixelGameEngine //: public NetworkCommon
{
public:
	Server server;
	ZombieSpawner zombieSpawner;
	std::list<ZombieServer*> zombieList;
	std::list<ObjectServer*> instanceList;
	sf::Clock elapsedClock;
	sf::Time fElapsedTime;
	
	GameServer();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

#endif