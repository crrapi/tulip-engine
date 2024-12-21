// src/engine/engine.cc
#include "engine.h"

// Core Systems
#include "src/core/logging.h"
#include "src/core/time.h"
#include "src/core/memory.h"

// Platform
#include "src/platform/platform.h"

// Subsystems
#include "src/subsystems/renderer/renderer.h"
#include "src/subsystems/audio/audio.h"
#include "src/subsystems/physics/physics.h"
#include "src/subsystems/input/input.h"
#include "src/subsystems/scripting/scripting.h"
#include "src/subsystems/ai/ai_system.h"
#include "src/subsystems/networking/network_client.h"
#include "src/subsystems/networking/network_server.h"
#include "src/subsystems/tools/level_editor.h"

// ECS
#include "src/ecs/world.h"

// Resources
#include "src/resources/resource_manager.h"

namespace Engine
{

    GameEngine::GameEngine()
        : mInitialized(false)
    {
    }

    GameEngine::~GameEngine()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    void GameEngine::Initialize()
    {
        if (mInitialized)
            return;

        Core::Logging::Log("[Engine] Initializing Tulip Engine...");

        // Initialize core systems
        Core::Memory::Initialize();
        Core::Time::Initialize();

        // Initialize platform and create the main window
        Platform::Initialize();
        Platform::CreateMainWindow("Tulip Engine", 1280, 720);

        // Initialize subsystems
        Input::Get().Initialize();
        Renderer::Get().Initialize();
        Audio::Get().Initialize();
        Physics::Get().Initialize();
        Scripting::Get().Initialize();
        AI::Get().Initialize();
        Networking::Server::Get().Initialize(12345);           // Initialize ENet server on port 12345
        Networking::Client::Get().Connect("127.0.0.1", 12345); // Connect ENet client to server

        // Initialize resource manager
        Resources::Manager::Get().Initialize();

        // Initialize ECS
        ECS::World::Get().Initialize();

        // Initialize tools (e.g., in-game level editor)
        Tools::LevelEditor::Get().Initialize();

        mInitialized = true;
        Core::Logging::Log("[Engine] Tulip Engine initialized successfully.");
    }

    void GameEngine::Update(float deltaTime)
    {
        if (!mInitialized)
            return;

        // Update core time
        Core::Time::Tick(deltaTime);

        // Update input subsystem
        Input::Get().Update();

        // Update physics subsystem
        Physics::Get().Update(deltaTime);

        // Update ECS
        ECS::World::Get().Update(deltaTime);

        // Update AI subsystem
        AI::Get().Update(deltaTime);

        // Update networking subsystem
        Networking::Server::Get().Update();
        Networking::Client::Get().Update();

        // Update scripting subsystem
        Scripting::Get().Update(deltaTime);

        // Update tools subsystem
        Tools::LevelEditor::Get().Update(deltaTime);

        // Render the frame
        Renderer::Get().RenderFrame();
    }

    void GameEngine::Shutdown()
    {
        if (!mInitialized)
            return;

        Core::Logging::Log("[Engine] Shutting down Tulip Engine...");

        // Shutdown tools
        Tools::LevelEditor::Get().Shutdown();

        // Shutdown ECS
        ECS::World::Get().Shutdown();

        // Shutdown resource manager
        Resources::Manager::Get().Shutdown();

        // Shutdown networking
        Networking::Server::Get().Shutdown();
        Networking::Client::Get().Shutdown();

        // Shutdown subsystems
        AI::Get().Shutdown();
        Scripting::Get().Shutdown();
        Physics::Get().Shutdown();
        Audio::Get().Shutdown();
        Renderer::Get().Shutdown();
        Input::Get().Shutdown();

        // Shutdown platform and destroy the main window
        Platform::DestroyMainWindow();
        Platform::Shutdown();

        // Shutdown core systems
        Core::Time::Shutdown();
        Core::Memory::Shutdown();

        mInitialized = false;
        Core::Logging::Log("[Engine] Tulip Engine shutdown complete.");
    }

} // namespace Engine
