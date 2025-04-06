#ifndef NETWORKING_H
#define NETWORKING_H

#include <SFML/Network.hpp>
#include <unordered_map>
#include "../shared/NetworkCommands.h"
#include "PlayerServer.h"

class GameServer;

class Client
{
public:
	sf::TcpSocket socket;
	sf::Packet packetRx;
	sf::Clock disconnectTimer;
	sf::Time disconnectDuration;

	PlayerServer player;

	int8_t Id = -1;
	std::string name = "";
};

class Server
{
public:
	sf::TcpListener listener;
	std::unordered_map<int8_t, Client> clients;
	int8_t socketId = 0;

	Server();
	bool connectClient();
	void receive(GameServer* game);
	void update(GameServer* game);
};

#endif 