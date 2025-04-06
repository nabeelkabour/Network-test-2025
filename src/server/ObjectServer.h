#pragma once

#include "../shared/olcGeoPixel.h"
#include "../shared/GameMechanics/Basic.h"

class GameServer;

class ObjectServer : public Basic
{
public:
	//void* collisionMask = nullptr;

	virtual void loop(GameServer* engine) = 0;
};

//template<typename T>
//class ObjectServer : public Basic
//{
//public:
//	T collisionMask;
//
//	virtual void loop(GameServer* engine) = 0;
//};

//template<typename T>
//class CollisionMask
//{
//public:
//	T collisionMask;
//};