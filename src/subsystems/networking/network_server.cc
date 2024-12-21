// src/subsystems/networking/network_server.cc
#include "network_server.h"
#include "src/core/logging.h"

namespace Networking
{

    static Server gServer;

    Server::Server()
        : mInitialized(false), mServerHost(nullptr)
    {
    }

    Server::~Server()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool Server::Initialize(int port)
    {
        if (enet_initialize() != 0)
        {
            Core::Logging::Log("[NetworkServer] Failed to initialize ENet.", Core::LogLevel::ERROR);
            return false;
        }

        ENetAddress address;
        address.host = ENET_HOST_ANY;
        address.port = port;

        mServerHost = enet_host_create(&address, 32, 2, 0, 0);
        if (!mServerHost)
        {
            Core::Logging::Log("[NetworkServer] Failed to create ENet server host.", Core::LogLevel::ERROR);
            return false;
        }

        mInitialized = true;
        Core::Logging::Log("[NetworkServer] ENet server initialized on port " + std::to_string(port) + ".");
        return true;
    }

    void Server::Update()
    {
        if (!mInitialized || !mServerHost)
            return;

        ENetEvent event;
        while (enet_host_service(mServerHost, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                Core::Logging::Log("[NetworkServer] A new client connected.");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                Core::Logging::Log("[NetworkServer] Packet received from client.");
                // Echo back the received packet
                enet_host_broadcast(mServerHost, 0, event.packet);
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                Core::Logging::Log("[NetworkServer] A client disconnected.");
                break;
            default:
                break;
            }
        }
    }

    void Server::Shutdown()
    {
        if (mServerHost)
        {
            enet_host_destroy(mServerHost);
            mServerHost = nullptr;
        }

        enet_deinitialize();
        mInitialized = false;
        Core::Logging::Log("[NetworkServer] ENet server shutdown complete.");
    }

    Server &Get()
    {
        return gServer;
    }

} // namespace Networking
