#include <iostream>
#include "Networking.h"
#include "Game.h"

Server::Server()
{

}

bool Server::connectClient()
{
	if (listener.accept(clients[socketId].socket) == sf::Socket::Status::Done)
	{
		clients[socketId].socket.setBlocking(false);
		clients[socketId].Id = socketId;

		++socketId;
		return true;
	}

	clients.erase(socketId);

	return false;
}

void Server::receive(Game* game)
{
	for (auto iterator = clients.begin();  iterator != clients.end() ;)
	{
		auto& client = iterator->second;
		auto receiveStatus = client.socket.receive(client.packetRx);
	
		if (receiveStatus == sf::Socket::Status::Done)
		{
			uint16_t cmd;
			client.packetRx >> cmd;

			switch (cmd)
			{
			case Cmd::ping:
			{
				sf::Packet packetTx;
				packetTx << Cmd::ping;

				client.socket.send(packetTx);
			}
			break;

			case Cmd::position:
			{
				float posX, posY;
				client.packetRx >> posX >> posY;
				game->position = { posX, posY };
				//std::cout << game.position.x << "   " << game.position.y << "\n";
			}
			break;
			}
		}
	}
}

void Server::update(Game* game)
{
	connectClient();
	receive(game);
}