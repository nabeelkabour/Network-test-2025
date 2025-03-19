#ifndef GAME_H
#define GAME_H

#include "../shared/olcPixelGameEngine.h"
#include "Client.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 360

class Game : public olc::PixelGameEngine
{
public:
	Client client;
	olc::vf2d position = { 0.f, 0.f };

	Game();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

extern Game game;

#endif