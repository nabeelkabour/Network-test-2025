#include "../shared/olcGeoPixel.h"
#include "ObjectServer.h"

class GameServer;

class PlayerServer : public ObjectServer//, public Player
{
public:
	olc::vf2d position;
	float direction;
	olc::vf2d velocity = { 0.f, 0.f };
	float recoil = 0.f;
	float recoilStrength = 5.f;
	float headAngleOffset = 0.f;
	bool canShoot = false;
	olc::utils::geom2d::circle<float> collisionMask;
	float gunDamage = 25.f;

	void create();
	void loop(GameServer* engine) override;
};
