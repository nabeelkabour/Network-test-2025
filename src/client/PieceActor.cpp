#include "PieceActor.h"
#include "GameClient.h"

PieceActor::PieceActor(olc::vf2d pos) : position(pos) {}

void PieceActor::draw(GameClient* engine)
{
	//for (auto* piece : pieceSlots)
	for(uint8_t index = 0; index < NUM_SLOTS; ++index)
	{
		if (pieceSlots[index])
		{
			engine->DrawRotatedDecal(
				position,
				pieceSlots[index],
				direction,
				pieceSlots[index]->sprite->Size() / 2,
				{ 1.f, 1.f },
				pieceColors[index]
			);
		}
	}
}

//void PieceActor::loop(GameClient* engine)
//{
//	position += velocity * engine->GetElapsedTime();
//	collisionMask.pos = position;
//}