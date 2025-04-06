#pragma once

//#include "GameClient.h"
#include "../shared/GameMechanics/Basic.h"
#include "../shared/olcGeoPixel.h"

class GameClient;

class Drawable : public Basic
{
public:
	int16_t depth = 0;
	bool drawFlag = true;

	virtual void draw(GameClient* engine) = 0;
};  