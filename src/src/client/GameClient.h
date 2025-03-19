#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include "../shared/olcPixelGameEngine.h"
#include "Client.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 360

class GameClient : public olc::PixelGameEngine
{
public:
	Client client;
	olc::vf2d position = { 0.f, 0.f };

	GameClient();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

#endif