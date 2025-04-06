#pragma once

enum ZombieState
{
	walking,
	attacking
};

//class Zombie
//{
//public:
//	int16_t zombieId = -1;
//	PlayerServer* target = nullptr;
//
//	float speed = 20.f;
//	olc::vf2d position;
//	olc::vf2d velocity = { 0.f, 0.f };
//	circle<float> collisionMask;
//	ZombieState state = ZombieState::walking;
//
//	Zombie();
//	Zombie(int32_t id, olc::vf2d pos, Player* _target = nullptr);
//	void create(); 
//	void move(olc::PixelGameEngine* engine);
//	void destroy();
//};