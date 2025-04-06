#include "../shared/Resources.h"
#include "PlayerClient.h"
#include "GameClient.h"

PlayerClient::PlayerClient(olc::vf2d pos) : PieceActor(pos) {}

void PlayerClient::create()
{
    pieceSlots[Pieces::body] = Resources::get().basicBody.Decal();
    pieceSlots[Pieces::bodyAccess] = Resources::get().basicBodyAccess.Decal();
    pieceSlots[Pieces::arms] = Resources::get().basicArms.Decal();
    pieceSlots[Pieces::sleeves] = Resources::get().basicSleeves.Decal();
    //pieceSlots[Pieces::armLeft] = Resources::get().basicArmLeft.Decal();
    //pieceSlots[Pieces::armRight] = Resources::get().basicArmRight.Decal();
    //pieceSlots[Pieces::handLeft] = Resources::get().basicHandLeft.Decal();
    //pieceSlots[Pieces::handRight] = Resources::get().basicHandRight.Decal();
    pieceSlots[Pieces::weapon] = Resources::get().basicWeapon.Decal();
    pieceSlots[Pieces::head] = Resources::get().basicHead.Decal();
    pieceSlots[Pieces::headAccess] = Resources::get().basicHeadAccess.Decal();

    for (auto& p : pieceColors)
    {
        p = olc::WHITE;
    }

    pieceColors[Pieces::body] = olc::DARK_GREEN;
    pieceColors[Pieces::headAccess] = olc::RED;
    pieceColors[Pieces::sleeves] = olc::BLUE;
    pieceColors[Pieces::arms] = olc::Pixel(255, 203, 164);
    pieceColors[Pieces::head] = olc::Pixel(255, 203, 164);
    pieceColors[Pieces::bodyAccess] = olc::Pixel(255, 0, 255);

    position = { 250.f, 250.f };
}

void PlayerClient::loop(GameClient* engine)
{
    float fElapsedTime = engine->GetElapsedTime();

    position += velocity * fElapsedTime;
    collisionMask.pos = position;

    //rect<float> tangle;
    //tangle.pos;
    //tangle.size = { 100.f, 100.f };

    if (recoil > 0)
    {
        recoil -= 15.f * fElapsedTime;
    }
}

void PlayerClient::draw(GameClient* engine)
{
    for (uint8_t index = 0; index < NUM_SLOTS; ++index)
    {
        olc::vf2d offset = { 0.f, 0.f };
        if (index == Pieces::sleeves || index == Pieces::weapon || index == Pieces::arms)
        {
            offset = { recoil, float(direction + pi) };
        }

        float headAngle = 0.f;
        olc::vf2d pivot = { 32.f, 36.f };// = { 48.f, 48.f };

        pivot = { 48.f, 48.f };

        if (index == Pieces::head || index == Pieces::headAccess)
        {
            headAngleOffset += 0.5f * engine->GetElapsedTime();
            headAngle = pi / 16.f * sin(headAngleOffset) + pi / 8.f;//rand() % 180) * (pi / 180.f);

            //pivot = { 65.f, 60.f };
        }

        //if (index == Pieces::weapon) /*pivot = { 48.f, 48.f };*/

        engine->DrawRotatedDecal(position + offset.cart(),
            pieceSlots[index],
            direction + headAngle,
            pivot/*pieceSlots[index]->sprite->Size() / 2.f*/,
            { 1.f, 1.f },
            pieceColors[index]
        );
    }

    //engine->DrawRotatedDecal(position, Resources::get().disk.Decal(), 0.f, {32.f, 32.f});//collisionMask.radius, collisionMask.radius});
}

void PlayerClient::destroy(GameClient* engine)
{
    loopFlag = false;
    drawFlag = false;
}