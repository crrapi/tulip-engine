// src/subsystems/renderer/renderer.cc
#include "renderer.h"
#include "src/core/logging.h"
#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "scene.h"
#include <glad/glad.h> // Include GLAD or your OpenGL loader
#include <SDL.h>

namespace
{
    Renderer::RendererSystem gRenderer;
}

namespace Renderer
{

    RendererSystem::RendererSystem()
        : mInitialized(false)
    {
    }

    RendererSystem::~RendererSystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    void RendererSystem::Initialize()
    {
        Core::Logging::Log("[Renderer] Initializing Renderer System...");

        // Initialize OpenGL loader (GLAD)
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            Core::Logging::Log("[Renderer] Failed to initialize GLAD.", Core::LogLevel::ERROR);
            return;
        }

        // Set OpenGL options
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        mInitialized = true;
        Core::Logging::Log("[Renderer] Renderer System initialized successfully.");
    }

    void RendererSystem::RenderFrame()
    {
        if (!mInitialized)
            return;

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the scene
        Scene::Get().Render();

        // Swap buffers
        SDL_Window *window = SDL_GL_GetCurrentWindow();
        if (window)
        {
            SDL_GL_SwapWindow(window);
        }
    }

    void RendererSystem::Shutdown()
    {
        Core::Logging::Log("[Renderer] Shutting down Renderer System...");
        // Cleanup resources if any
        mInitialized = false;
    }

    RendererSystem &Get()
    {
        return gRenderer;
    }

} // namespace Renderer
