#pragma once

#include "../olcPixelGameEngine.h"

class Player
{
public:
	//olc::vf2d position = { 100.f, 100.f };
	olc::vf2d velocity = { 0.f, 0.f };	
	float recoil = 0.f;
	float recoilStrength = 5.f;
	float headAngleOffset = 0.f;
	bool canShoot = true;
	//bool canShoot = true;

	circle<float> collisionMask;

	Player();
	void loop(float fElapsedTime);
	void create();
	//void draw(NetworkCommon* engine) override;
};