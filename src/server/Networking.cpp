#include <iostream>
#include "Networking.h"
#include "GameServer.h"
#include "ZombieServer.h"

Server::Server()
{

}

bool Server::connectClient()
{
	if (listener.accept(clients[socketId].socket) == sf::Socket::Status::Done)
	{
		clients[socketId].socket.setBlocking(false);
		clients[socketId].Id = socketId;

		clients[socketId].player.create();

		sf::Packet packetTx;

		//Send back to connecting client
		packetTx << Cmd::confirmNewConnection;
		packetTx << socketId;

		clients[socketId].socket.setBlocking(true);
		clients[socketId].socket.send(packetTx);
		clients[socketId].socket.setBlocking(false);

		packetTx.clear();
		packetTx << Cmd::newClientConnected;
		packetTx << socketId;

		std::string newName = "Test name";
		packetTx << newName;

		//Send to other clients
		for (auto& c : clients)
		{
			auto& client = c.second;
			if (socketId == client.Id) continue;

			client.socket.setBlocking(true);
			client.socket.send(packetTx);
			client.socket.setBlocking(false);
		}

		//Sync old clients
		for (auto& c : clients)
		{
			if (c.first == socketId) continue;

			packetTx.clear();
			packetTx << Cmd::syncClientConnected;
			packetTx << c.first;
			packetTx << c.second.player.position.x;
			packetTx << c.second.player.position.y;

			clients[socketId].socket.setBlocking(true);
			clients[socketId].socket.send(packetTx);
			clients[socketId].socket.setBlocking(false);
		}

		++socketId;

		return true;
	}

	clients.erase(socketId);

	return false;
}

void Server::receive(GameServer* game)
{
	for (auto iterator = clients.begin();  iterator != clients.end() ;)
	{
		auto& client = iterator->second;
		auto receiveStatus = client.socket.receive(client.packetRx);
	
		if (receiveStatus == sf::Socket::Status::Done)
		{
			client.disconnectTimer.restart();

			uint16_t cmd;
			client.packetRx >> cmd;

			//std::cout << cmd << "\n";

			switch (cmd)
			{
			case Cmd::ping:
			{
				float posX, posY;
				client.packetRx >> posX >> posY;

				clients[iterator->first].player.position = { posX, posY };

				sf::Packet packetTx;
				packetTx << Cmd::ping;

				client.socket.setBlocking(true);
				client.socket.send(packetTx);
				client.socket.setBlocking(false);
			}
			break;

			case Cmd::move:
			{
				float spdX, spdY, posX, posY;
				float dir;
				//int8_t moveId;
				//client.packetRx >> moveId;
				client.packetRx >> spdX >> spdY;
				client.packetRx >> posX >> posY;
				client.packetRx >> dir;

				clients[iterator->first].player.velocity = { spdX, spdY };
				clients[iterator->first].player.position = { posX, posY };
				clients[iterator->first].player.direction = dir;

				//std::cout << "Received velocity packet:  " << spdX << "   " << spdY << "\n";
				//std::cout << "Received move packet:  " << posX << "   " << posY << "\n";

				//Send to all other clients
				sf::Packet packetTx;
				packetTx << Cmd::move;
				packetTx << iterator->first;
				packetTx << spdX << spdY;
				packetTx << posX << posY;
				packetTx << dir;

				for (auto& c : clients)
				{
					int8_t currentSocket = c.first;

					if (iterator->first == currentSocket) continue;

					c.second.socket.setBlocking(true);
					c.second.socket.send(packetTx);
					c.second.socket.setBlocking(false);
				}
			}
			break;

			case Cmd::syncRotation:
			{
				float dir;
				client.packetRx >> dir;

				clients[iterator->first].player.direction = dir;

				sf::Packet packetTx;
				packetTx << Cmd::syncRotation;
				packetTx << iterator->first;
				packetTx << dir;

				for (auto& c : clients)
				{
					int8_t currentSocket = c.first;

					if (iterator->first == currentSocket) continue;

					c.second.socket.setBlocking(true);
					c.second.socket.send(packetTx);
					c.second.socket.setBlocking(false);
				}
			}
			break;

			case Cmd::rifleShot:
			{				
				float fromX, fromY;
				float toX, toY;

				client.packetRx >> fromX >> fromY;
				client.packetRx >> toX >> toY;

				olc::vf2d start = { fromX, fromY };
				olc::utils::geom2d::line<float> lineCast(start, { toX, toY });

				for (ZombieServer* z : game->zombieList)
				{
					if (overlaps(lineCast, z->collisionMask))
					{						
						z->hp -= clients[client.Id].player.gunDamage;
						if (z->hp <= 0.f) z->destroy(game);
						//z->destroy(game);
					}
				}

				//for (ObjectServer* z : game->instanceList)
				//{
				//	if (overlaps(lineCast, z->collisionMask))
				//	{
				//		z->destroy(game);
				//	}
				//}

//				for (auto& c : clients)
//				{
//					if (c.first == client.Id) continue;
//
//					//std::cout << "Checking for collision.\n";
//
//					auto& clnt = c.second;
//					auto& points = intersects(lineCast, clnt.player.collisionMask);
//
//					if (overlaps(lineCast, clnt.player.collisionMask))
//					{
//						float distance = (points.back() - start).mag();
//
//						std::cout << "Target hit  " << distance << "\n";
//
///*						game->drawList.push_back(new GunShotEffect(lineCast));
//
//						olc::vf2d endPoint = { toX, toY };
//						if (points.size() > 1)
//						{
//							endPoint = points[1];
//						}
//
//						game->drawList.push_back(new GunShotEffect(points[0], endPoint, olc::RED));*/						
//					} 
//				}

				sf::Packet packetTx;
				packetTx << Cmd::rifleShot;
				packetTx << client.Id;
				packetTx << fromX << fromY;
				packetTx << toX << toY;

				for (auto& c : clients)
				{
					if (c.first == client.Id) continue;
					
					c.second.socket.setBlocking(true);
					c.second.socket.send(packetTx);
					c.second.socket.setBlocking(false);
				}

				//Effects
				//game->drawList.push_back(new GunShotEffect(lineCast));
			}
			break;

			}
		}

		//std::cout << client.disconnectDuration.asMilliseconds() << "\n";

		client.disconnectDuration = client.disconnectTimer.getElapsedTime();

		//std::cout << client.disconnectDuration.asMilliseconds() << "\n";

		if (client.disconnectDuration.asMilliseconds() >= 5000)
		{
			iterator = clients.erase(iterator);			
		}
		else
		{
			++iterator;
		}
	}
}

void Server::update(GameServer* game)
{
	connectClient();
	receive(game);
}