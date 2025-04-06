#pragma once

#include <SFML/Network.hpp>
#include "../shared/NetworkCommands.h"
#include "PlayerClient.h"

class GameClient;

class ClientOther
{
public:
    //sf::TcpSocket socket;
    //sf::Packet packetRx;

    PlayerClient player;

    int8_t Id = -1;
    std::string name = "";
};

class Client
{
public:
    sf::TcpSocket socket;
    sf::Packet packetRx;
    int8_t Id = -1;

    std::unordered_map<int8_t, ClientOther> otherClients;
    std::string name = "";

    PlayerClient player;

    std::chrono::time_point<std::chrono::steady_clock> pingStart;

    Client();
    void send(sf::Packet& packet);
    void update(GameClient* game);
    void ping();
};
