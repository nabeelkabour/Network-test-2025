#include "ZombieClient.h"
#include "PlayerClient.h"
#include "../shared/GameMechanics/Basic.h"
#include "ObjectClient.h"
#include "../shared/Resources.h" 
#include "GameClient.h"

ZombieClient::ZombieClient(int32_t id, olc::vf2d pos, PlayerClient* _target) :
	PieceActor(pos),
	zombieId(id),
	target(_target)
{
	collisionMask.radius = 32.f;

	//Send skin color to clients
}

//void ZombieClient::draw(GameClient* engine)
//{
//	PieceActor::draw(engine);
//}

void ZombieClient::create()
{
	pieceSlots[Pieces::body] = Resources::get().basicBody.Decal();
	pieceSlots[Pieces::bodyAccess] = nullptr;//Resources::get().basicBodyAccess.Decal();
	pieceSlots[Pieces::arms] = Resources::get().basicArms.Decal();
	pieceSlots[Pieces::sleeves] = nullptr;//Resources::get().basicSleeves.Decal();
	//pieceSlots[Pieces::armLeft] = Resources::get().basicArmLeft.Decal();
	//pieceSlots[Pieces::armRight] = Resources::get().basicArmRight.Decal();
	//pieceSlots[Pieces::handLeft] = Resources::get().basicHandLeft.Decal();
	//pieceSlots[Pieces::handRight] = Resources::get().basicHandRight.Decal();
	pieceSlots[Pieces::weapon] = nullptr;// Resources::get().basicWeapon.Decal();
	pieceSlots[Pieces::head] = Resources::get().basicHead.Decal();
	pieceSlots[Pieces::headAccess] = nullptr;// Resources::get().basicHeadAccess.Decal();

	for (auto& p : pieceColors)
	{
		p = olc::WHITE;
	}

	pieceColors[Pieces::arms] = skinColor;
	pieceColors[Pieces::head] = skinColor;
	pieceColors[Pieces::body] = clothesColor;
	//pieceColors[Pieces::sleeves] = clothesColor;
}

void ZombieClient::loop(GameClient* engine)
{
	/*move(engine);*/

	float fElapsedTime = engine->GetElapsedTime();

	position += velocity * fElapsedTime;
	collisionMask.pos = position;

	//std::cout << position << "\n";

	/*chaseTimer += fElapsedTime;*/

	//if (chaseTimer >= chaseInterval)
	//{
	if (target)
	{
		olc::vf2d d = target->position - position;
		float distance = d.mag();

		if (distance > collisionMask.radius)
		{
			//olc::vf2d anglePolar = olc::vf2d(0.f, prevDir);

			direction = d.polar().y;

			//if (prevDir > 0) prevDir -= fElapsedTime;
			//else if (prevDir < 0) prevDir += fElapsedTime;
			//else prevDir = 0;

			//if (prevDir > 0) prevDir -= fElapsedTime;
			//else if (prevDir < 0) prevDir += fElapsedTime;

			velocity = olc::vf2d(speed, direction).cart();
		}
		else
		{
			//state = ZombieState::attacking;

			speed = 0.f;
		}
	}
	else
	{
		velocity = olc::vf2d(speed, direction).cart();
	}
}

void ZombieClient::destroy(GameClient* engine)
{
	Basic::removeFlag = true;
	//drawFlag = true;
	//loopFlag = true;

	//Death effect.
	for (int8_t index = 0; index < NUM_SLOTS; ++index)
	{
		olc::Pixel color = clothesColor;
		if (index == Pieces::arms || index == Pieces::head) color = skinColor;

		engine->drawList.push_back(new ZombieBodyPart(position, pieceSlots[index], color));

		//engine->drawList.push_back(new ZombieBodyPart(position, p, skinColor, clothesColor));
	}
}

ZombieBodyPart::ZombieBodyPart(olc::vf2d pos, olc::Decal* spr, olc::Pixel c) :
	partSprite(spr),
	position(pos),
	color(c)
{
	dir = (rand() % 360) * olc::utils::geom2d::pi / 180.f;
	speed = rand() % 10 + 10;
	//lifeInterval = (rand() % 50 + 25.f) / 100.f;

	depth = 999;
}

void ZombieBodyPart::draw(GameClient* engine)
{
	if (partSprite)
	{
		olc::Pixel c = { color.r, color.g, color.b, uint8_t(255.f * alpha) };

		engine->DrawRotatedDecal(position, partSprite, dir, partSprite->sprite->Size() / 2.f,
			{ 1.f, 1.f },
			c
			);
	}
	else
	{
		removeFlag = true;
	}

	position += olc::vf2d(speed, dir).cart() * engine->GetElapsedTime();
	alpha -= engine->GetElapsedTime();

	if (alpha <= 0.f) removeFlag = true;

	//lifeTimer += engine->GetElapsedTime();
	//if (lifeTimer >= lifeInterval) removeFlag = true;
}