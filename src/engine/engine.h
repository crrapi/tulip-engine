// src/engine/engine.h
#pragma once

namespace Engine
{

    class GameEngine
    {
    public:
        GameEngine();
        ~GameEngine();

        void Initialize();
        void Update(float deltaTime);
        void Shutdown();

    private:
        bool mInitialized;
    };

} // namespace Engine
