// src/subsystems/input/input.h
#pragma once
#include <SDL.h>

namespace Input
{

    class InputSystem
    {
    public:
        InputSystem();
        ~InputSystem();

        bool Initialize();
        void Update();
        void Shutdown();

        bool ShouldQuit() const { return mShouldQuit; }

    private:
        bool mInitialized;
        bool mShouldQuit;
    };

    // Global accessor
    InputSystem &Get();

} // namespace Input
