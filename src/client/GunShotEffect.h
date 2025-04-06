#pragma once

#include "Drawable.h"

class GunShotEffect : public Drawable
{
public:
	olc::vf2d p1, p2;
	const float lifeTime = 1.f;
	float life = 0.f;
	olc::Pixel color = olc::YELLOW;
	float alpha = 1.f;

	GunShotEffect(olc::vf2d _p1, olc::vf2d _p2, olc::Pixel _col = olc::YELLOW);
	GunShotEffect(olc::utils::geom2d::line<float> _line);

	//void loop(GameClient* engine) override;
	void draw(GameClient* engine) override;
};