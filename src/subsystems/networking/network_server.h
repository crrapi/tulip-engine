// src/subsystems/networking/network_server.h
#pragma once
#include <enet/enet.h>
#include <string>

namespace Networking
{

    class Server
    {
    public:
        Server();
        ~Server();

        bool Initialize(int port);
        void Update();
        void Shutdown();

    private:
        bool mInitialized;
        ENetHost *mServerHost;
    };

    // Global accessor
    Server &Get();

} // namespace Networking
