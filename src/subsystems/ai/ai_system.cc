// src/subsystems/ai/ai_system.cc
#include "ai_system.h"
#include "src/core/logging.h"

namespace AI
{

    static AISystem gAISystem;

    AISystem::AISystem()
        : mInitialized(false)
    {
    }

    AISystem::~AISystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool AISystem::Initialize()
    {
        Core::Logging::Log("[AI] Initializing AI System...");
        // Initialize AI components, state machines, etc.
        mInitialized = true;
        Core::Logging::Log("[AI] AI System initialized successfully.");
        return true;
    }

    void AISystem::Update(float deltaTime)
    {
        if (!mInitialized)
            return;

        // Perform AI logic, e.g., decision making, state updates
        PerformAILogic();

        Core::Logging::Log("[AI] AI System updated.");
    }

    void AISystem::Shutdown()
    {
        Core::Logging::Log("[AI] Shutting down AI System...");
        // Cleanup AI components
        mInitialized = false;
        Core::Logging::Log("[AI] AI System shutdown complete.");
    }

    void AISystem::PerformAILogic()
    {
        // Example AI behavior logic
        Core::Logging::Log("[AI] Performing AI logic...");
    }

    AISystem &Get()
    {
        return gAISystem;
    }

} // namespace AI
