#pragma once

//#include "GameClient.h"
//#include "ObjectClient.h"
#include "Drawable.h"

#define NUM_SLOTS 7

class GameClient;

enum Pieces
{
    body,
    bodyAccess,
    arms,
    sleeves,
    weapon,
    head,
    headAccess
};

class PieceActor : public Drawable
{
public:
    olc::vf2d position;
    float direction = 0.f;

	olc::Decal* pieceSlots[NUM_SLOTS];
    olc::Pixel pieceColors[NUM_SLOTS];// = olc::WHITE;

    PieceActor(olc::vf2d pos);
    void draw(GameClient* engine) override;
};