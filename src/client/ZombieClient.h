
#pragma once

#include "ObjectClient.h"
//#include "GameClient.h"
#include "PieceActor.h"
#include "../shared/GameMechanics/Zombie.h"

class PlayerClient;

class ZombieClient : public ObjectClient, public PieceActor//, public Zombie
{
public:	
	int32_t zombieId;
	PlayerClient* target = nullptr;

	float speed = 20.f;
	//olc::vf2d position;
	olc::vf2d velocity = { 0.f, 0.f };
	olc::utils::geom2d::circle<float> collisionMask;
	ZombieState state = ZombieState::walking;
	float prevDir = 0.f;
	//float chaseTimer = 0.f;
	//float chaseInterval = 0.5f;
	olc::Pixel skinColor, clothesColor;

	ZombieClient(int32_t id, olc::vf2d pos, PlayerClient* _target);
	void create();
	void loop(GameClient* engine) override;
	//void draw(GameClient* engine) override;
	void destroy(GameClient* engine);
	//void move(GameClient* engine);
};

class ZombieBodyPart : public Drawable
{
public:
	olc::Decal* partSprite = nullptr;
	olc::vf2d position;
	float speed, dir;
	float alpha = 1.f;
	//float lifeInterval;
	//float lifeTimer = 0.f;
	olc::Pixel color;

	ZombieBodyPart(olc::vf2d pos, olc::Decal* spr, olc::Pixel c);
	void draw(GameClient* engine) override;
};