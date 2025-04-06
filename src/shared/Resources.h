#pragma once

#include "olcGeoPixel.h"

class Resources
{
	Resources();

public:
	static Resources& get()
	{
		static Resources res;
		return res;
	}

	Resources(Resources&&) = delete;
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	Resources& operator=(Resources&&) = delete;

	//Player
	olc::Renderable basicBody;
	olc::Renderable basicBodyAccess;
	olc::Renderable basicArms;
	olc::Renderable basicSleeves;
	//olc::Renderable basicArmLeft;
	//olc::Renderable basicArmRight;
	//olc::Renderable basicHandLeft;
	//olc::Renderable basicHandRight;
	olc::Renderable basicWeapon;
	olc::Renderable basicHead;
	olc::Renderable basicHeadAccess;

	//Effects
	olc::Renderable disk;
};