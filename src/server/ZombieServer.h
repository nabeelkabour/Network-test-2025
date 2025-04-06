#pragma once

#include "../shared/GameMechanics/Zombie.h"
#include "ObjectServer.h"

class GameServer;

class ZombieServer : public ObjectServer
{
public:
	static int32_t zombieCount;

	int32_t zombieId;
	PlayerServer* target = nullptr;
	olc::vf2d position;
	olc::vf2d velocity = { 0.f, 0.f };
	const float targetScanInterval = 0.5f;
	float targetScanTimer = 0.f;
	float hp = 100.f;
	ZombieState	state = ZombieState::walking;
	float speed = 20.f, direction = 0.f;
	circle<float> collisionMask;
	float chaseTimer = 0.f;
	float chaseInterval = 0.5f;
	olc::Pixel skinColor, clothesColor;

	//Zombie();
	ZombieServer(int32_t id, olc::vf2d pos, float _hp, PlayerServer * _target = nullptr);
	void create();
	void destroy(GameServer* engine);
	void loop(GameServer* engine);
};