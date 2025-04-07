#pragma once

#include "ObjectClient.h"
#include "PieceActor.h"

class GameClient;

class PlayerClient : public PieceActor, public ObjectClient//, public Player
{
public:
	//olc::vf2d position;
	//float direction;
	olc::vf2d velocity = { 0.f, 0.f };
	float recoil = 0.f;
	float recoilStrength = 5.f;
	float headAngleOffset = 0.f;
	bool canShoot = true;

	olc::utils::geom2d::circle<float> collisionMask;
	

	PlayerClient(olc::vf2d pos = { 0.f, 0.f });
	void loop(GameClient* engine) override;
	void create();
	void draw(GameClient* engine) override;
	void destroy(GameClient* engine);
};