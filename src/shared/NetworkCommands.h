#ifndef NETWORK_COMMANDS_H
#define NETWORK_COMMANDS_H

#include <iostream>

enum Cmd : uint16_t
{
    ping,

    confirmNewConnection,
    newClientConnected,
    syncClientConnected,
    disconnect,

    rifleShot,

    move,
    syncRotation,
    position,

    spawnZombie,
    syncZombie,
    destroyZombie,

    newPoint
};

//clientConnected,
//sendName,
//listNames,
//ready,
//gameStart,
//broadcastNewClient,
//syncPrevClients,
//click,
//message,
//move,
//position,

#endif 
