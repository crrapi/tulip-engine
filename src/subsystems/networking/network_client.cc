// src/subsystems/networking/network_client.cc
#include "network_client.h"
#include "src/core/logging.h"

namespace Networking
{

    static Client gClient;

    Client::Client()
        : mInitialized(false), mClientHost(nullptr), mServerPeer(nullptr)
    {
    }

    Client::~Client()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool Client::Initialize()
    {
        if (enet_initialize() != 0)
        {
            Core::Logging::Log("[NetworkClient] Failed to initialize ENet.", Core::LogLevel::ERROR);
            return false;
        }

        mClientHost = enet_host_create(NULL, 1, 2, 0, 0);
        if (!mClientHost)
        {
            Core::Logging::Log("[NetworkClient] Failed to create ENet client host.", Core::LogLevel::ERROR);
            return false;
        }

        mInitialized = true;
        Core::Logging::Log("[NetworkClient] ENet client initialized successfully.");
        return true;
    }

    bool Client::Connect(const std::string &host, int port)
    {
        if (!mInitialized || !mClientHost)
            return false;

        ENetAddress address;
        enet_address_set_host(&address, host.c_str());
        address.port = port;

        mServerPeer = enet_host_connect(mClientHost, &address, 2, 0);
        if (!mServerPeer)
        {
            Core::Logging::Log("[NetworkClient] No available peers for initiating connection.", Core::LogLevel::ERROR);
            return false;
        }

        Core::Logging::Log("[NetworkClient] Attempting to connect to " + host + ":" + std::to_string(port));
        return true;
    }

    void Client::Update()
    {
        if (!mInitialized || !mClientHost)
            return;

        ENetEvent event;
        while (enet_host_service(mClientHost, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                Core::Logging::Log("[NetworkClient] Connected to server.");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                Core::Logging::Log("[NetworkClient] Packet received from server.");
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                Core::Logging::Log("[NetworkClient] Disconnected from server.");
                mServerPeer = nullptr;
                break;
            default:
                break;
            }
        }
    }

    void Client::Shutdown()
    {
        if (mServerPeer)
        {
            enet_peer_disconnect_now(mServerPeer, 0);
            mServerPeer = nullptr;
        }

        if (mClientHost)
        {
            enet_host_destroy(mClientHost);
            mClientHost = nullptr;
        }

        enet_deinitialize();
        mInitialized = false;
        Core::Logging::Log("[NetworkClient] ENet client shutdown complete.");
    }

    Client &Get()
    {
        return gClient;
    }

} // namespace Networking
