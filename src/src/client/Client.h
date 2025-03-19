#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include "../shared/NetworkCommands.h"

class Client
{
public:
    sf::TcpSocket socket;
    int8_t socketId = -1;
    sf::Packet packetRx;

    std::chrono::time_point<std::chrono::steady_clock> pingStart;

    Client();
    void send(sf::Packet& packet);
    void update();
    void ping();
};

#endif 