#include "./SFML/Network.hpp"
#include "../shared/olcGeoPixel.h"
#include "../shared/GameMechanics/Zombie.h"
#include "../shared/NetworkCommands.h"
#include "GameServer.h"
#include "ZombieSpawner.h"
#include "ZombieServer.h"

//class olc::PixelGameEngine;
//class GameServer;

int32_t ZombieSpawner::spawnId = 0;

void ZombieSpawner::loop(GameServer* engine)
{
	spawnTimer += engine->GetElapsedTime();

	if (spawnTimer >= spawnInterval)
	{
		//Spawn zombie
		int8_t targetPlayerId = 0;
		float posX = 450, posY = 125;
		float hp = 100.f;

		float distance = 999.f;
		auto& clientMap = engine->server.clients;
		for (auto& c : clientMap)
		{
			float currentDistance = (c.second.player.position - olc::vf2d{ posX, posY }).mag();
			if (currentDistance < distance)
			{
				distance = currentDistance;
				targetPlayerId = c.first;
			}
		}

		ZombieServer* z = new ZombieServer(spawnId, { posX, posY }, hp, &clientMap[targetPlayerId].player);
		z->create();
		engine->zombieList.push_back(z);
		engine->instanceList.push_back(z);

		sf::Packet packetTx;
		packetTx << Cmd::spawnZombie;
		packetTx << spawnId;
		packetTx << targetPlayerId;
		packetTx << posX << posY;
		packetTx << z->skinColor.r << z->skinColor.g << z->skinColor.b;
		packetTx << z->clothesColor.r << z->clothesColor.g << z->clothesColor.b;
		
		for (auto& c : engine->server.clients)
		{
			c.second.socket.setBlocking(true);
			c.second.socket.send(packetTx);
			c.second.socket.setBlocking(false);
		}

		std::cout << "Zombie spawned at " << posX << ", " << posY << "\n";

		++spawnId;

		spawnTimer = 0.f;
	}
}