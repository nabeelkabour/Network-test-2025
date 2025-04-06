#include "GameServer.h"
#include "ZombieServer.h"

ZombieServer::ZombieServer(int32_t id, olc::vf2d pos, float _hp, PlayerServer* _target) :
	zombieId(id),
	position(pos),
	hp(_hp),
	target(_target)
{
	collisionMask.radius = 32.f;
}


int32_t ZombieServer::zombieCount = 0;

void ZombieServer::loop(GameServer* engine)
{
	//move(engine);

	float fElapsedTime = engine->GetElapsedTime();

	position += velocity * fElapsedTime;
	collisionMask.pos = position;

	//std::cout << position << "\n";

	//chaseTimer += fElapsedTime;

	//if (chaseTimer >= chaseInterval)
	//{
	//	chaseTimer = 0.f;

	switch (state)
	{
	case ZombieState::walking:
	{
		int8_t targetId = -1;
		PlayerServer* playerNearest = nullptr;

		targetScanTimer += fElapsedTime; // engine->GetElapsedTime();

		if (targetScanTimer >= targetScanInterval)
		{
			float distance = 9999.f;
			auto& clientMap = engine->server.clients;	
			for (auto& c : clientMap)
			{
				float currentDistance = (c.second.player.position - position).mag();
				if (currentDistance < distance)
				{
					distance = currentDistance;
					targetId = c.first;
//						playerNearest = &c.second.player;
				}
			}

			playerNearest = &engine->server.clients[targetId].player;

			//std::cout << "target " << targetId <<  "\n";

			if (playerNearest != target)
			{
				//std::cout << "New target aquired.\n";

				target = playerNearest;

				//Send to clients
				sf::Packet packetTx;
				packetTx << Cmd::syncZombie;
				packetTx << zombieId;
				packetTx << targetId;
				packetTx << position.x << position.y;

				for (auto& c : engine->server.clients)
				{
					c.second.socket.setBlocking(true);
					c.second.socket.send(packetTx);
					c.second.socket.setBlocking(false);
				}
			}

			targetScanTimer = 0.f;
		}

		if (target)
		{
			olc::vf2d d = target->position - position;
			float distance = d.mag();

			if (distance > collisionMask.radius)
			{
				direction = d.polar().y;

				velocity = olc::vf2d(speed, direction).cart();

			}
			else
			{
				//state = ZombieState::attacking;

				speed = 0.f;
			}
		}
		else
		{
			velocity = olc::vf2d(speed, direction).cart();
		}
	}
	break;

	case ZombieState::attacking:
	{
		//***
	}
	break;

	}
}

void ZombieServer::destroy(GameServer* engine)
{
	sf::Packet packetTx;

	packetTx << Cmd::destroyZombie;
	packetTx << zombieId;
	packetTx << position.x << position.y;

	for (auto& c : engine->server.clients)
	{
		c.second.socket.setBlocking(true);
		c.second.socket.send(packetTx);
		c.second.socket.setBlocking(false);
	}

	--zombieCount;
	
	removeFlag = true;

	std::cout << "Zombie hit!\n";
}

void ZombieServer::create()
{
	++zombieCount;

	olc::Pixel c;
	
	switch (rand() % 3)
	{
	case 0:
	{
		c = { 88, 57, 39 };
	}
	break;

	case 1:
	{
		c = { 255, 229, 180 };
	}
	break;

	case 2:
	{
		c = { 30, 15, 0 };
	}
	break;

	}

	skinColor = c;//olc::Pixel(rand() % 255, rand() % 255, rand() % 255);
	clothesColor = olc::Pixel(rand() % 255, rand() % 255, rand() % 255);
}