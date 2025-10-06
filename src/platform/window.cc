// src/platform/window.cc
#include "window.h"
#include "src/core/logging.h"
#include <SDL.h>
#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

namespace Platform
{

    static SDL_Window *gWindow = nullptr;
    static SDL_GLContext gGLCtx = nullptr;

    void Window::Create(const char *title, int width, int height)
    {
        // Set OpenGL version (3.2 Core for broad macOS compatibility)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
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

        // Set viewport
        glViewport(0, 0, width, height);

        Core::Logging::Log("[Window] Window and OpenGL context created successfully.");
    }

    void Window::SwapBuffers()
    {
        if (gWindow)
        {
            SDL_GL_SwapWindow(gWindow);
        }
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
