#include "../shared/olcGeoPixel.h"
#include "GameClient.h"
#include "../shared/Resources.h"
#include "ZombieClient.h"
#include "Blood.h"
#include "GunShotEffect.h"
#include "../shared/GameMechanics/Basic.h"
#include "ObjectClient.h"

#define and &&
#define or ||

GameClient::GameClient()
{
	sAppName = "Client";
}

bool GameClient::OnUserCreate()
{
	client.socket.connect({ 127,0,0,1 }, 2000); //{ 81,106,245,122 }, { 127,0,0,1 }
	client.socket.setBlocking(false);

	Resources::get();

	client.player.create();

	camera = olc::utils::Camera2D(GetScreenSize());
	
	camera.SetTarget(client.player.position);
	camera.SetMode(olc::utils::Camera2D::Mode::LazyFollow);
	camera.SetWorldBoundary({ 0.0f, 0.0f }, { 200.f, 200.f }); //float(ScreenWidth()), float(ScreenHeight()) });
	camera.EnableWorldBoundary(false);

	loopList.push_back(&client.player);
	drawList.push_back(&client.player);

	loopList.push_back(&zombies);
	drawList.push_back(&zombies);

	//Zombie* z = new Zombie;
	//z->create();
	////zombies.push_back(z);
	//drawList.push_back(z);

	return true;
}

bool GameClient::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);

	client.update(this);

	camera.Update(fElapsedTime);
	tv.SetWorldOffset(camera.GetViewPosition());

	PlayerClient& cPlayer = client.player;

	//trackedPoint = cPlayer.position;

	if (cPlayer.canShoot and GetMouse(0).bPressed)
	{
		//std::cout << cPlayer.direction << "\n";
		olc::vf2d startPoint = cPlayer.position + olc::vf2d{ 64.f, cPlayer.direction }.cart();
		olc::vf2d endPoint = startPoint + olc::vf2d{ 400.f, cPlayer.direction }.cart();
		//olc::vf2d endPoint = { float(GetMouseX()), float(GetMouseY()) };
		line<float> lineCast(startPoint, endPoint);

		//DrawLineDecal(startPoint, endPoint);

		sf::Packet packetTx;
		packetTx << Cmd::rifleShot;
		packetTx << startPoint.x << startPoint.y;
		packetTx << endPoint.x << endPoint.y;

		client.send(packetTx);

		drawList.push_back(new GunShotEffect(lineCast));

		//for (auto& c : client.otherClients)
		//{
		//	//auto& points = intersects(lineCast);

		//	//for (auto& p : points)
		//	//{
		//	//	drawList.push_back(new BloodShotEffect(p, 0.f));
		//	//}
		//}

		for (ZombieClient* z : zombies.instances)
		{
			auto& bloodPoints = intersects(lineCast, z->collisionMask);

			for (auto& p : bloodPoints)
			{
				drawList.push_back(new BloodShotEffect(p, 0.f));
			}
		}

		client.player.recoil = client.player.recoilStrength;
		//cPlayer.canShoot = false;
	}

	static float timer = 0.f;
	timer += fElapsedTime;

	if (timer >= 1.f)
	{
		timer = 0.f;

		client.ping();
	}

	static float timerSyncRot = 0.f;
	timerSyncRot += fElapsedTime;
	static float prevDir = 0.f;

	if (abs(prevDir - client.player.direction) >= (pi / 24.f) and timerSyncRot >= (1.f / 30.f))
	{
		sf::Packet packetTx;

		packetTx << Cmd::syncRotation;
		packetTx << client.player.direction;

		client.send(packetTx);

		prevDir = client.player.direction;
		//std::cout << prevDir << "\n";
	}

	olc::vf2d pos_change = { 0, 0 };
	if (GetKey(olc::W).bHeld) pos_change.y -= 1;// * fElapsedTime;
	if (GetKey(olc::S).bHeld) pos_change.y += 1;// * fElapsedTime;
	if (GetKey(olc::A).bHeld) pos_change.x -= 1;// * fElapsedTime;
	if (GetKey(olc::D).bHeld) pos_change.x += 1;// * fElapsedTime;

	olc::vf2d vel = { 0.f, 0.f };

	if (pos_change.mag2() != 0.f)
	{
		//vel = pos_change.norm() * 150;
		//client.player.velocity = vel;
		vel = pos_change.norm() * 150;
		//vel.cart();		
	}

	client.player.velocity = vel;// .cart();

	if (GetKey(olc::W).bPressed
		or GetKey(olc::A).bPressed
		or GetKey(olc::S).bPressed
		or GetKey(olc::D).bPressed
		or GetKey(olc::W).bReleased
		or GetKey(olc::A).bReleased
		or GetKey(olc::S).bReleased
		or GetKey(olc::D).bReleased)
	{
		sf::Packet packetTx;

		packetTx << Cmd::move;
		packetTx << vel.x << vel.y;
		packetTx << client.player.position.x << client.player.position.y;
		packetTx << client.player.direction;

		client.send(packetTx);
	}

	olc::vf2d d = olc::vf2d{ float(GetMouseX()), float(GetMouseY()) } - client.player.position;
	client.player.direction = atan2(d.y, d.x);

	for (ObjectClient* o : loopList)
	{
		if (o->loopFlag)
		{
			o->loop(this);
		}
	}

	drawList.sort([&](const Drawable* d1, const Drawable* d2) { return d1->depth > d2->depth; });

	for (Drawable* d : drawList)
	{
		if (d->drawFlag)
		{
			d->draw(this);
		}
	}

	//zombieList.remove_if([&](const ZombieClient* z) { return z->Basic::removeFlag; });
	zombies.instances.remove_if([&](const ZombieClient* z)
		{
			if (z->Basic::removeFlag)
			{
				delete z;
				return true;
			}
			else
			{
				return false;
			}
		});
	
	drawList.remove_if([&](const Drawable* d)
		{
			if (d->Basic::removeFlag)
			{
				if (dynamic_cast<const ObjectClient*>(d) == nullptr) delete d;
				return true;
			}
			else
			{
				return false;
			}
		});


	loopList.remove_if([&](const ObjectClient* o)
		{
			if (o->Basic::removeFlag)
			{
				delete o;
				return true;
			}
			else
			{
				return false;
			}
		});

	return true;
}

//void GameClient::AddLoopDraw(DrawObject* dObj)
//{
//	loopList.push_back(dObj);
//	drawList.push_back(dObj);
//}

//void ZombieList::loop(GameClient * engine)
//{
//	for (ZombieClient* z : zombies)
//	{
//		z->loop(engine);
//	}
//}
//
//void ZombieList::draw(GameClient* engine) 
//{
//	for (ZombieClient* z : zombies)
//	{
//		z->draw(engine);
//	}
//}