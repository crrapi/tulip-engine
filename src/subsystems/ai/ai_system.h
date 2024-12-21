// src/subsystems/ai/ai_system.h
#pragma once

namespace AI
{

    class AISystem
    {
    public:
        AISystem();
        ~AISystem();

        bool Initialize();
        void Update(float deltaTime);
        void Shutdown();

        // Example AI behavior methods
        void PerformAILogic();

    private:
        bool mInitialized;
    };

    // Global accessor
    AISystem &Get();

} // namespace AI
