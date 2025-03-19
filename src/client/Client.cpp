#include "Game.h"
#include "Client.h"
#include <chrono>
#include <iostream>

Client::Client()
{

}

void Client::update()
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

            std::cout << elapsed_seconds.count() * 1000 << "\n";

            break;
        }
        }
    }
}


void Client::ping()
{
    sf::Packet pingPacket;
    pingPacket << Cmd::ping;

    send(pingPacket);

    pingStart = std::chrono::steady_clock::now();
}

void Client::send(sf::Packet& packet)
{
    socket.setBlocking(true);
    socket.send(packet);
    socket.setBlocking(false);
}