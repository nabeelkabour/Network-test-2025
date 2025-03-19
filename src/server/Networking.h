#ifndef NETWORKING_H
#define NETWORKING_H

#include <SFML/Network.hpp>
#include <unordered_map>
#include "../shared/NetworkCommands.h"
#include "Game.h"
//#include "Networking.h"

class Client
{
public:
	sf::TcpSocket socket;
	sf::Packet packetRx;

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
	void receive(Game* game);
	void update(Game* game);
};

#endif 