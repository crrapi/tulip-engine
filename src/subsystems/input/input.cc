// src/subsystems/input/input.cc
#include "input.h"
#include "src/core/logging.h"

namespace Input
{

    static InputSystem gInputSystem;

    InputSystem::InputSystem()
        : mInitialized(false), mShouldQuit(false)
    {
    }

    InputSystem::~InputSystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool InputSystem::Initialize()
    {
        Core::Logging::Log("[Input] Initializing Input System...");
        mInitialized = true;
        return true;
    }

    void InputSystem::Update()
    {
        if (!mInitialized)
            return;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mShouldQuit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                mShouldQuit = true;
            }
            // Handle more input events as needed
        }
    }

    void InputSystem::Shutdown()
    {
        Core::Logging::Log("[Input] Shutting down Input System...");
        mInitialized = false;
    }

    InputSystem &Get()
    {
        return gInputSystem;
    }

} // namespace Input
