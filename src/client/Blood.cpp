#include "../shared/olcGeoPixel.h"
#include "Blood.h"
#include "../shared/Resources.h"
#include "GameClient.h"

BloodShotEffect::BloodShotEffect(olc::vf2d pos, float dir) //direction(dir)
{
	//velocity = { float(rand() % 15 - 15), float(rand() % 15 - 15) };
	for (uint8_t i = 0; i < 4; ++i)
	{
		position[i] = pos;

		float mag = rand() % 100 + 50.f;
		float dirV = rand() % 360 * (olc::utils::geom2d::pi / 180.f);

		velocity[i].x = mag;
		velocity[i].y = dirV;

		float s = (rand() % 5) * 0.05f;
		size[i] = {s,s};
	}

	depth = -1;
}

void BloodShotEffect::draw(GameClient* engine)
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		float elapsedTime = engine->GetElapsedTime();
		position[i] += velocity[i].cart() * elapsedTime;
		alpha -= 0.5f * elapsedTime;

		if (alpha <= 0.f) removeFlag = true;

		olc::Pixel col(255, 0, 0, 255 * alpha);

		engine->DrawDecal(position[i], Resources::get().disk.Decal(), size[i], col);
	}
	//engine->Circle(position, 4, col);
}