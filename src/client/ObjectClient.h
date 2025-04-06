#pragma once

#include "../shared/GameMechanics/Basic.h"
#include "Drawable.h"

class GameClient;

class ObjectClient : public Basic
{
public:
	bool loopFlag = true;

	virtual void loop(GameClient* engine) = 0;
};

class DrawObject : public ObjectClient, public Drawable
{

};