//#include "Zombie.h"
//#include "../Resources.h"
//#include "../olcUTIL_Geometry2D.h"
//
////Zombie::Zombie()
////{
////	position = { 200.f, 200.f };
////
////	collisionMask.radius = 32.f;
////
////	depth = 1;
////}
////
////Zombie::Zombie(int32_t id, olc::vf2d pos, Player* _target) : target(_target)
////{
////	zombieId = id;
////	position = pos;
////	collisionMask.radius = 32.f;
////	depth = 1;
////}
//
//void Zombie::create()
//{
//	//pieceSlots[Pieces::body] = Resources::get().basicBody.Decal();
//	//pieceSlots[Pieces::bodyAccess] = Resources::get().basicBodyAccess.Decal();
//	//pieceSlots[Pieces::armLeft] = Resources::get().basicArmLeft.Decal();
//	//pieceSlots[Pieces::armRight] = Resources::get().basicArmRight.Decal();
//	//pieceSlots[Pieces::handLeft] = Resources::get().basicHandLeft.Decal();
//	//pieceSlots[Pieces::handRight] = Resources::get().basicHandRight.Decal();
//	//pieceSlots[Pieces::weapon] = nullptr;// Resources::get().basicWeapon.Decal();
//	//pieceSlots[Pieces::head] = Resources::get().basicHead.Decal();
//	//pieceSlots[Pieces::headAccess] = nullptr;// Resources::get().basicHeadAccess.Decal();
//
//	//for (auto& p : pieceColors)
//	//{
//	//	p = olc::WHITE;
//	//}
//}
//
////void Zombie::loop(olc::PixelGameEngine* engine)
////{
////	position += velocity * engine->GetElapsedTime();
////	collisionMask.pos = position;
////
////	Player* playerNearest = nullptr;
////
////	if (targetScanTimer >= targetScanInterval)
////	{
////		float distance = 999.f;
////		auto& clientMap = engine->server.clients;
////		for (auto& c : clientMap)
////		{
////			float currentDistance = (c.second.player.position - olc::vf2d{ posX, posY }).mag();
////			if (currentDistance < distance)
////			{
////				distance = currentDistance;
////				targetPlayer = c.first;
////			}
////		}
////
////		targetScanTimer = 0.f;
////	}
////}
//
////void Zombie::move(olc::PixelGameEngine* engine)
////{
////	position += velocity * engine->GetElapsedTime();
////	collisionMask.pos = position;
////}