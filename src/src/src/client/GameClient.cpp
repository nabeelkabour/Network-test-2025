#include "GameClient.h"


GameClient::GameClient()
{
	sAppName = "Client";
}


bool GameClient::OnUserCreate()
{
	client.socket.connect({ 127,0,0,1 }, 2000); //{ 81,106,245,122 }, { 127,0,0,1 }
	client.socket.setBlocking(false);

	return true;
}

bool GameClient::OnUserUpdate(float fElapsedTime)
{
	client.update();

	static float timer = 0.f;
	timer += fElapsedTime;

	if (timer >= 1.f)
	{
		client.ping();
		timer = 0.f;
	}

	position = { float(GetMouseX()), float(GetMouseY()) };

	sf::Packet packetTx;
	packetTx << Cmd::position << position.x << position.y;

	client.send(packetTx);

	Draw(position);

	return true;
}

