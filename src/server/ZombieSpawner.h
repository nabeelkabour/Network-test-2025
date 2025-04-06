#pragma once

class GameServer;
class ZombieServer;

class ZombieSpawner
{
public:
	const float spawnInterval = 4.f;
	float spawnTimer = 0.f;

	static int32_t spawnId;

	//void destroy(GameServer* engine);
	void loop(GameServer* engine);
};