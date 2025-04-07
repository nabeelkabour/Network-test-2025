#pragma once

#include "../shared/olcGeoPixel.h"
#include "../shared/olcUTIL_Camera2D.h"
//#include "Drawable.h"
//#include "ObjectClient.h"
#include "Client.h"
#include "ZombieClient.h"

class Drawable;
class ObjectClient;
class Basic;
class ZombieClient;

//class ZombieList : public ObjectClient, public Drawable
//{
//public:
//	std::list<ZombieClient*> zombies;
//
//	void loop(GameClient* engine) override;
//	void draw(GameClient* engine) override;
//};

template<typename T>
class List : public Drawable, public ObjectClient
{
public:
	std::list<T*> instances;

	void loop(GameClient* engine) override
	{
		for (T* o : instances)
		{
			o->loop(engine);
		}
	}

	void draw(GameClient* engine) override
	{
		for (T* d : instances)
		{
			d->draw(engine);
		}
	}
};

//template<>
//void List<ZombieClient>::loop(GameClient* engine)
//{
//	for (ZombieClient* o : instances)
//	{
//		o->loop(engine);
//	}
//}

class GameClient : public olc::PixelGameEngine
{
public:
	Client client;

	//std::list<std::shared_ptr<ObjectClient*>> loopList;
	//std::list<std::shared_ptr<Drawable*>> drawList;
	//std::list<std::shared_ptr<ZombieClient*>> zombieList;
	olc::utils::Camera2D camera;
	olc::TransformedView tv;
	olc::vf2d trackedPoint;

	std::list<ObjectClient*> loopList;
	std::list<Drawable*> drawList;
	//std::list<ZombieClient*> zombieList;
	List<ZombieClient> zombies;

	GameClient();
	//void AddLoopDraw(DrawObject* dObj);
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};