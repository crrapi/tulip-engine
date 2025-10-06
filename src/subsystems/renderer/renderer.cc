// src/subsystems/renderer/renderer.cc
#include "renderer.h"
#include "src/core/logging.h"
#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "scene.h"
#include "src/platform/window.h"
#include <vector>
#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

namespace
{
    Renderer::RendererSystem gRenderer;
}

namespace Renderer
{

    RendererSystem::RendererSystem()
        : mInitialized(false), mSampleSetupDone(false), mRotation(0.0f)
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

        // Set OpenGL options
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE); // Disable culling so we can see the triangle from any side

        // Setup sample triangle
        std::vector<float> vertices = {
            -0.5f,
            -0.5f,
            0.0f,
            0.5f,
            -0.5f,
            0.0f,
            0.0f,
            0.5f,
            0.0f,
        };
        std::vector<unsigned int> indices = {0, 1, 2};

        auto mesh = std::make_shared<Mesh>();
        mesh->Load(vertices, indices);
        Scene::Get().AddMesh(mesh);

        const char *vs = R"(#version 150 core
in vec3 aPos;
uniform float uRotation;
void main(){
    float c = cos(uRotation);
    float s = sin(uRotation);
    mat2 rot = mat2(c, s, -s, c);
    vec2 rotated = rot * aPos.xy;
    gl_Position = vec4(rotated, aPos.z, 1.0);
}
)";
        const char *fs = R"(#version 150 core
out vec4 FragColor;
uniform float uRotation;
void main(){
    float pulse = (sin(uRotation * 2.0) + 1.0) * 0.5;
    vec3 color1 = vec3(1.0, 0.5, 0.2);
    vec3 color2 = vec3(0.2, 0.8, 1.0);
    FragColor = vec4(mix(color1, color2, pulse), 1.0);
}
)";
        auto mat = std::make_shared<Material>();
        mat->LoadFromSource(vs, fs);
        Scene::Get().SetDefaultMaterial(mat);

        mInitialized = true;
        mSampleSetupDone = true;
        Core::Logging::Log("[Renderer] Renderer System initialized successfully with sample triangle.");
    }

    void RendererSystem::RenderFrame()
    {
        if (!mInitialized)
            return;

        // Update rotation
        mRotation += 0.02f;

        // Clear the screen to a nice dark blue
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set rotation uniform
        Scene::Get().SetMaterialFloat("uRotation", mRotation);

        // Render the scene
        Scene::Get().Render();

        // Swap buffers
        Platform::Window::SwapBuffers();
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
