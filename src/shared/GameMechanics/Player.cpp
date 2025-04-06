#include "Player.h"
#include "../Resources.h"
#include "../NetworkCommon.h"

//Player::Player()
//{
//    collisionMask.radius = 32.f;
//
//    depth = 1;
//}

void Player::create()
{
    //pieceSlots[Pieces::body] = Resources::get().basicBody.Decal();
    //pieceSlots[Pieces::bodyAccess] = Resources::get().basicBodyAccess.Decal();
    //pieceSlots[Pieces::armLeft] = Resources::get().basicArmLeft.Decal();
    //pieceSlots[Pieces::armRight] = Resources::get().basicArmRight.Decal();
    //pieceSlots[Pieces::handLeft] = Resources::get().basicHandLeft.Decal();
    //pieceSlots[Pieces::handRight] = Resources::get().basicHandRight.Decal();
    //pieceSlots[Pieces::weapon] = Resources::get().basicWeapon.Decal();
    //pieceSlots[Pieces::head] = Resources::get().basicHead.Decal();
    //pieceSlots[Pieces::headAccess] = Resources::get().basicHeadAccess.Decal();

    //for (auto& p : pieceColors)
    //{
    //    p = olc::WHITE;
    //}

    //pieceColors[Pieces::body] = olc::DARK_GREEN;
    //pieceColors[Pieces::headAccess] = olc::RED;

    //collisionMask.radius = pieceSlots[Pieces::body]->sprite->width / 2.f;
}

//void Player::loop(float fElapsedTime)
//{
//
//	position += velocity * fElapsedTime;
//    collisionMask.pos = position;
//
//    if (recoil > 0)
//    {
//        recoil -= 15.f * fElapsedTime;
//    }
//}