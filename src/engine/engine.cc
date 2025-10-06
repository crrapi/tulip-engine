// src/engine/engine.cc
#include "engine.h"

// Core Systems
#include "src/core/logging.h"
#include "src/core/time.h"
#include "src/core/memory.h"

// Platform
#include "src/platform/platform.h"

// Subsystems (slimmed to essentials)
#include "src/subsystems/renderer/renderer.h"
#include "src/subsystems/input/input.h"

// ECS
#include "src/ecs/world.h"

// Resources (removed for minimal runnable sample)

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

        // Initialize subsystems (minimal)
        Input::Get().Initialize();
        Renderer::Get().Initialize();

        // Initialize ECS
        ECS::World::Get().Initialize();

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

        // Update ECS
        ECS::World::Get().Update(deltaTime);

        // Render the frame
        Renderer::Get().RenderFrame();
    }

    void GameEngine::Shutdown()
    {
        if (!mInitialized)
            return;

        Core::Logging::Log("[Engine] Shutting down Tulip Engine...");

        // Shutdown ECS
        ECS::World::Get().Shutdown();

        // Shutdown subsystems (minimal)
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
