// src/subsystems/networking/network_client.h
#pragma once
#include <enet/enet.h>
#include <string>

namespace Networking
{

    class Client
    {
    public:
        Client();
        ~Client();

        bool Initialize();
        bool Connect(const std::string &host, int port);
        void Update();
        void Shutdown();

    private:
        bool mInitialized;
        ENetHost *mClientHost;
        ENetPeer *mServerPeer;
    };

    // Global accessor
    Client &Get();

} // namespace Networking
