#ifndef GAME_H
#define GAME_H

#include "../shared/olcPixelGameEngine.h"
#include "Networking.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 360

class Game : public olc::PixelGameEngine
{
public:
	Server server;
	olc::vf2d position = { 100.f, 100.f };

	Game();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

#endif