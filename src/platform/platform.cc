// src/platform/platform.cc
#include "platform.h"
#include "window.h"
#include "src/core/logging.h"
#include <SDL.h>

namespace Platform
{

    void Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
        {
            Core::Logging::Log("[Platform] SDL_Init failed: " + std::string(SDL_GetError()), Core::LogLevel::ERROR);
        }
        else
        {
            Core::Logging::Log("[Platform] SDL initialized successfully.");
        }
    }

    void Shutdown()
    {
        Core::Logging::Log("[Platform] Shutting down SDL...");
        SDL_Quit();
    }

    void CreateMainWindow(const char *title, int width, int height)
    {
        Window::Create(title, width, height);
    }

    void DestroyMainWindow()
    {
        Window::Destroy();
    }

} // namespace Platform
