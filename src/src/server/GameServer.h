#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "../shared/olcPixelGameEngine.h"
#include "Networking.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 360

class GameServer : public olc::PixelGameEngine
{
public:
	Server server;
	olc::vf2d position = { 100.f, 100.f };

	GameServer();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

#endif