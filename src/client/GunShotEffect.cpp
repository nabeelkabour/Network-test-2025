#include "GunShotEffect.h"
#include "GameClient.h"

GunShotEffect::GunShotEffect(olc::vf2d _p1, olc::vf2d _p2, olc::Pixel _col) : p1(_p1), p2(_p2), color(_col)
{
	depth = 2;
}

GunShotEffect::GunShotEffect(olc::utils::geom2d::line<float> _line)
{
	p1 = _line.start;
	p2 = _line.end;

	depth = 2;
}

void GunShotEffect::draw(GameClient* engine)
{
	olc::Pixel col = color;
	col.a = 255 * alpha;
	engine->DrawLineDecal(p1, p2, col);

	alpha -= engine->GetElapsedTime() * 3;
	if (alpha <= 0.f) removeFlag = true;

	//life += engine->GetElapsedTime();
	/*if (life >= 1.f) removeFlag = true;*/
}