#ifndef NETWORK_COMMANDS_H
#define NETWORK_COMMANDS_H

enum Cmd : uint16_t
{
    ping,
    disconnect,
    clientConnected,
    sendName,
    listNames,
    ready,
    gameStart,
    broadcastNewClient,
    syncPrevClients,
    click,
    message,
    move,
    position
};


#endif 
