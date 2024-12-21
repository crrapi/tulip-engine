// src/platform/window.cc
#include "window.h"
#include "src/core/logging.h"
#include <SDL.h>
#include <glad/glad.h> // Or your chosen OpenGL loader

namespace Platform
{

    static SDL_Window *gWindow = nullptr;
    static SDL_GLContext gGLCtx = nullptr;

    void Window::Create(const char *title, int width, int height)
    {
        // Set OpenGL version (e.g., 3.3 Core)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create the window with OpenGL context
        gWindow = SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width, height,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!gWindow)
        {
            Core::Logging::Log("[Window] Failed to create SDL window: " + std::string(SDL_GetError()), Core::LogLevel::ERROR);
            return;
        }

        // Create OpenGL context
        gGLCtx = SDL_GL_CreateContext(gWindow);
        if (!gGLCtx)
        {
            Core::Logging::Log("[Window] Failed to create OpenGL context: " + std::string(SDL_GetError()), Core::LogLevel::ERROR);
            return;
        }

        // Initialize OpenGL loader here if necessary (e.g., GLAD, GLEW)
        // Example with GLAD:
        /*
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            Core::Logging::Log("[Window] Failed to initialize GLAD.", Core::LogLevel::ERROR);
            return;
        }
        */

        // Set viewport
        glViewport(0, 0, width, height);

        Core::Logging::Log("[Window] Window and OpenGL context created successfully.");
    }

    void Window::Destroy()
    {
        if (gGLCtx)
        {
            SDL_GL_DeleteContext(gGLCtx);
            gGLCtx = nullptr;
        }
        if (gWindow)
        {
            SDL_DestroyWindow(gWindow);
            gWindow = nullptr;
        }
        Core::Logging::Log("[Window] Window destroyed.");
    }

} // namespace Platform
