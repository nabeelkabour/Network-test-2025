#include "GameClient.h"
#include "Client.h"
#include "PlayerClient.h"
#include "ZombieClient.h"
#include "GunShotEffect.h"
#include "Blood.h"
#include <chrono>
#include <iostream>

Client::Client()
{

}

void Client::update(GameClient* game)
{
    auto receiveStatus = socket.receive(packetRx);

    if (receiveStatus == sf::Socket::Status::Done)
    {
        uint16_t cmd;
        packetRx >> cmd;
        
        switch (cmd)
        {
        case Cmd::ping:
        {
            std::chrono::time_point<std::chrono::steady_clock> pingFinish = std::chrono::steady_clock::now();
            const std::chrono::duration<double> elapsed_seconds = pingFinish - pingStart;

            //std::cout << elapsed_seconds.count() * 1000 << "\n";          
        }
        break;

        case Cmd::confirmNewConnection:
        {
            packetRx >> Id;

            //Sync zombies.
        }
        break;

        case Cmd::newClientConnected:
        {
            int8_t connectingId;
            std::string name;
            packetRx >> connectingId;
            packetRx >> name;

            otherClients[connectingId].Id = connectingId;
            otherClients[connectingId].name = name;
            otherClients[connectingId].player.create();

            //game
            game->loopList.push_back(&otherClients[connectingId].player);
            game->drawList.push_back(&otherClients[connectingId].player);
        }
        break;

        case Cmd::syncClientConnected:
        {
            int8_t Id;
            float posX, posY;
            packetRx >> Id;
            packetRx >> posX >> posY;

            otherClients[Id].player.position = { posX, posY };
            otherClients[Id].Id = Id;
            otherClients[Id].player.create();

            game->loopList.push_back(&otherClients[Id].player);
            game->drawList.push_back(&otherClients[Id].player);
        }
        break;

        //case Cmd::newPoint:
        //{
        //    float posX, posY;
        //    packetRx >> posX >> posY;

        //    game->DrawCircle(posX, posY, 3);

        //    break;
        //}

        case Cmd::move:
        {
            int8_t moveId;
            float spdX, spdY;
            float posX, posY;
            float dir;

            packetRx >> moveId;
            packetRx >> spdX >> spdY;
            packetRx >> posX >> posY;
            packetRx >> dir;

            otherClients[moveId].player.velocity = { spdX, spdY };
            otherClients[moveId].player.position = { posX, posY };
            otherClients[moveId].player.direction = dir;
        }
        break;

        case Cmd::syncRotation:
        {
            int8_t rotId;
            float dir;
            packetRx >> rotId;
            packetRx >> dir;

            otherClients[rotId].player.direction = dir;
        }
        break;

        case Cmd::rifleShot:
        {
            int8_t shooterId;
            float fromX, fromY, toX, toY;
            packetRx >> shooterId;
            packetRx >> fromX >> fromY;
            packetRx >> toX >> toY;

            //Shooter recoil animation
            otherClients[shooterId].player.recoil = otherClients[shooterId].player.recoilStrength;

            line<float> shotCast = { { fromX, fromY }, { toX, toY } };
            game->drawList.push_back(new GunShotEffect(shotCast));

            //auto& points = intersects(shotCast, player.collisionMask);

            //for (auto& p : points)
            //{
            //    //std::cout << p << "\n";
            //    game->drawList.push_back(new BloodShotEffect(p, 0.f));
            //}

            for (ZombieClient* z : game->zombies.instances)
            {
                auto& bloodPoints = intersects(shotCast, z->collisionMask);

                for (auto& p : bloodPoints)
                {
                    game->drawList.push_back(new BloodShotEffect(p, 0.f));
                }
            } 

            for (auto& c : otherClients)
            {
                auto& points = intersects(shotCast, c.second.player.collisionMask);
                //std::cout << c.second.player.collisionMask.pos << "\n";
                for (auto& p : points)
                {
                    game->drawList.push_back(new BloodShotEffect(p, 0.f));
                }
            }
        }
        break;

        case Cmd::spawnZombie:
        {
            int32_t zombieId;
            int8_t targetPlayerId;
            float posX, posY;
            packetRx >> zombieId;
            packetRx >> targetPlayerId;
            packetRx >> posX >> posY;

            PlayerClient* p;

            if (Id == targetPlayerId) p = &player;
            else
            {
                p = &otherClients[targetPlayerId].player;
            }

            ZombieClient* z = new ZombieClient(zombieId,
                { posX, posY },
                p
            );

            packetRx >> z->skinColor.r >> z->skinColor.g >> z->skinColor.b;
            packetRx >> z->clothesColor.r >> z->clothesColor.g >> z->clothesColor.b;

            z->create();
            game->zombies.instances.push_back(z);
            //game->loopList.push_back(z);
            //game->drawList.push_back(z);

            //std::cout << "Zombie spawned.\n";
        }
        break;

        case Cmd::syncZombie:
        {
            int32_t syncZombieId;
            packetRx >> syncZombieId;

            ZombieClient* zombie = nullptr;

            for (ZombieClient* z : game->zombies.instances)
            {
                if (z->zombieId == syncZombieId)
                {
                    zombie = z;
                    break;
                }
            }

            if (zombie == nullptr) break;

            int8_t targetPlayerId;
            float posX, posY;

            packetRx >> targetPlayerId;
            packetRx >> posX >> posY;

            PlayerClient* p = nullptr;

            if (Id == targetPlayerId) p = &player;
            else
            {
                p = &otherClients[targetPlayerId].player;
            }

            zombie->prevDir = zombie->direction;
            zombie->target = p;
            zombie->position = { posX, posY };
        }
        break;

        case Cmd::destroyZombie:
        {
            int32_t destroyId;
            float posX, posY;

            packetRx >> destroyId;
            packetRx >> posX >> posY;

            ZombieClient* z = nullptr;

            for (ZombieClient* zom : game->zombies.instances)
            {
                if (zom->zombieId == destroyId)
                {
                    z = zom;
                    z->position = { posX, posY };
                    break;
                }
            }

            if (z)
            {
                z->destroy(game);
                //z->Basic::removeFlag = true;
            }
        }
        break;

        }
    }
}


void Client::ping()
{
    sf::Packet pingPacket;
    pingPacket << Cmd::ping;
    pingPacket << player.position.x << player.position.y;

    send(pingPacket);

    pingStart = std::chrono::steady_clock::now();
}

void Client::send(sf::Packet& packet)
{
    socket.setBlocking(true);
    socket.send(packet);
    socket.setBlocking(false);
}