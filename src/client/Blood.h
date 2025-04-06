#pragma once

#include "Drawable.h"

class BloodShotEffect : public Drawable
{
public:
	olc::vf2d position[4];
	olc::vf2d velocity[4];
	olc::vf2d size[4];
	//float direction;
	float alpha = 1.f;

	BloodShotEffect(olc::vf2d pos, float dir);
	void draw(GameClient* engine) override;
};