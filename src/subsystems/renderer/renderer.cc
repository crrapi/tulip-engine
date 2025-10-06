// src/subsystems/renderer/renderer.cc
#include "renderer.h"
#include "src/core/logging.h"
#include "src/core/time.h"
#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "scene.h"
#include "src/platform/window.h"
#include <vector>
#include <string>
#include <cmath>
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
        : mInitialized(false), mSampleSetupDone(false), mRotation(0.0f),
          mDebugVAO(0), mDebugVBO(0), mDebugShaderID(0)
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Setup multiple triangles for epic background
        // Main spinning triangle
        std::vector<float> vertices1 = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
        std::vector<unsigned int> indices1 = {0, 1, 2};
        auto mesh1 = std::make_shared<Mesh>();
        mesh1->Load(vertices1, indices1);
        Scene::Get().AddMesh(mesh1);

        // Background triangle 1 (larger, slower)
        std::vector<float> vertices2 = {-0.8f, -0.8f, -0.5f, 0.8f, -0.8f, -0.5f, 0.0f, 0.8f, -0.5f};
        std::vector<unsigned int> indices2 = {0, 1, 2};
        auto mesh2 = std::make_shared<Mesh>();
        mesh2->Load(vertices2, indices2);
        Scene::Get().AddMesh(mesh2);

        // Background triangle 2
        std::vector<float> vertices3 = {-0.3f, 0.6f, -0.3f, -0.7f, 0.0f, -0.3f, -0.3f, -0.6f, -0.3f};
        std::vector<unsigned int> indices3 = {0, 1, 2};
        auto mesh3 = std::make_shared<Mesh>();
        mesh3->Load(vertices3, indices3);
        Scene::Get().AddMesh(mesh3);

        // Background triangle 3
        std::vector<float> vertices4 = {0.3f, 0.6f, -0.3f, 0.7f, 0.0f, -0.3f, 0.3f, -0.6f, -0.3f};
        std::vector<unsigned int> indices4 = {0, 1, 2};
        auto mesh4 = std::make_shared<Mesh>();
        mesh4->Load(vertices4, indices4);
        Scene::Get().AddMesh(mesh4);

        const char *vs = R"(#version 150 core
in vec3 aPos;
uniform float uRotation;
out float vDepth;
void main(){
    float speed = 1.0 + aPos.z * 0.5;
    float c = cos(uRotation * speed);
    float s = sin(uRotation * speed);
    mat2 rot = mat2(c, s, -s, c);
    vec2 rotated = rot * aPos.xy;
    vDepth = aPos.z;
    gl_Position = vec4(rotated, aPos.z, 1.0);
}
)";
        const char *fs = R"(#version 150 core
in float vDepth;
out vec4 FragColor;
uniform float uRotation;
void main(){
    float pulse = (sin(uRotation * 2.0) + 1.0) * 0.5;
    float depthFactor = (vDepth + 1.0) * 0.5;
    
    vec3 color1 = vec3(1.0, 0.5, 0.2);
    vec3 color2 = vec3(0.2, 0.8, 1.0);
    vec3 color3 = vec3(0.8, 0.2, 0.9);
    
    vec3 mixColor = mix(color1, color2, pulse);
    mixColor = mix(mixColor, color3, depthFactor * 0.5);
    
    float alpha = 0.3 + depthFactor * 0.7;
    FragColor = vec4(mixColor, alpha);
}
)";
        auto mat = std::make_shared<Material>();
        mat->LoadFromSource(vs, fs);
        Scene::Get().SetDefaultMaterial(mat);

        SetupDebugOverlay();

        mInitialized = true;
        mSampleSetupDone = true;
        Core::Logging::Log("[Renderer] Renderer System initialized successfully with sample triangle.");
    }

    void RendererSystem::SetupDebugOverlay()
    {
        // Create simple shader for debug overlay
        const char *debugVS = R"(#version 150 core
in vec2 aPos;
in vec3 aColor;
out vec3 vColor;
void main(){
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)";
        const char *debugFS = R"(#version 150 core
in vec3 vColor;
out vec4 FragColor;
void main(){
    FragColor = vec4(vColor, 0.9);
}
)";

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &debugVS, nullptr);
        glCompileShader(vs);

        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &debugFS, nullptr);
        glCompileShader(fs);

        mDebugShaderID = glCreateProgram();
        glAttachShader(mDebugShaderID, vs);
        glAttachShader(mDebugShaderID, fs);
        glBindAttribLocation(mDebugShaderID, 0, "aPos");
        glBindAttribLocation(mDebugShaderID, 1, "aColor");
        glLinkProgram(mDebugShaderID);

        glDeleteShader(vs);
        glDeleteShader(fs);

        glGenVertexArrays(1, &mDebugVAO);
        glGenBuffers(1, &mDebugVBO);
    }

    void RendererSystem::RenderFrame()
    {
        if (!mInitialized)
            return;

        // Update rotation
        mRotation += 0.02f;

        // Animated background color
        float bgPulse = (std::sin(mRotation * 0.5f) + 1.0f) * 0.5f;
        float r = 0.1f + bgPulse * 0.15f;
        float g = 0.15f + bgPulse * 0.2f;
        float b = 0.25f + bgPulse * 0.25f;
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set rotation uniform
        Scene::Get().SetMaterialFloat("uRotation", mRotation);

        // Render the scene
        Scene::Get().Render();

        // Render debug overlay
        RenderDebugOverlay();

        // Swap buffers
        Platform::Window::SwapBuffers();
    }

    void RendererSystem::RenderDebugOverlay()
    {
        // Render FPS as a visual bar graph in top-left corner
        glDisable(GL_DEPTH_TEST);
        glUseProgram(mDebugShaderID);
        glBindVertexArray(mDebugVAO);

        float fps = Core::Time::GetFPS();
        float fpsNormalized = std::min(fps / 120.0f, 1.0f); // Normalize to 0-1 range (max 120 FPS display)

        // Create vertices for FPS bar and background
        std::vector<float> debugVerts;

        // Background panel (dark semi-transparent)
        float panelW = 0.4f;
        float panelH = 0.15f;
        float panelX = -0.95f;
        float panelY = 0.85f;

        // Panel background vertices (pos.xy + color.rgb)
        debugVerts.insert(debugVerts.end(), {
                                                panelX,
                                                panelY,
                                                0.1f,
                                                0.1f,
                                                0.15f,
                                                panelX + panelW,
                                                panelY,
                                                0.1f,
                                                0.1f,
                                                0.15f,
                                                panelX + panelW,
                                                panelY + panelH,
                                                0.1f,
                                                0.1f,
                                                0.15f,

                                                panelX,
                                                panelY,
                                                0.1f,
                                                0.1f,
                                                0.15f,
                                                panelX + panelW,
                                                panelY + panelH,
                                                0.1f,
                                                0.1f,
                                                0.15f,
                                                panelX,
                                                panelY + panelH,
                                                0.1f,
                                                0.1f,
                                                0.15f,
                                            });

        // FPS bar (green to red based on performance)
        float barX = panelX + 0.02f;
        float barY = panelY + 0.02f;
        float barW = (panelW - 0.04f) * fpsNormalized;
        float barH = 0.04f;

        float r = 1.0f - fpsNormalized;
        float g = fpsNormalized;

        debugVerts.insert(debugVerts.end(), {
                                                barX,
                                                barY,
                                                r,
                                                g,
                                                0.2f,
                                                barX + barW,
                                                barY,
                                                r,
                                                g,
                                                0.2f,
                                                barX + barW,
                                                barY + barH,
                                                r,
                                                g,
                                                0.2f,

                                                barX,
                                                barY,
                                                r,
                                                g,
                                                0.2f,
                                                barX + barW,
                                                barY + barH,
                                                r,
                                                g,
                                                0.2f,
                                                barX,
                                                barY + barH,
                                                r,
                                                g,
                                                0.2f,
                                            });

        // Frame count indicator (smaller bar)
        int frames = Core::Time::GetFrameCount();
        float frameBarY = barY + 0.05f;
        float frameBarW = (panelW - 0.04f) * (std::fmod(frames, 60) / 60.0f);

        debugVerts.insert(debugVerts.end(), {
                                                barX,
                                                frameBarY,
                                                0.2f,
                                                0.8f,
                                                1.0f,
                                                barX + frameBarW,
                                                frameBarY,
                                                0.2f,
                                                0.8f,
                                                1.0f,
                                                barX + frameBarW,
                                                frameBarY + barH,
                                                0.2f,
                                                0.8f,
                                                1.0f,

                                                barX,
                                                frameBarY,
                                                0.2f,
                                                0.8f,
                                                1.0f,
                                                barX + frameBarW,
                                                frameBarY + barH,
                                                0.2f,
                                                0.8f,
                                                1.0f,
                                                barX,
                                                frameBarY + barH,
                                                0.2f,
                                                0.8f,
                                                1.0f,
                                            });

        glBindBuffer(GL_ARRAY_BUFFER, mDebugVBO);
        glBufferData(GL_ARRAY_BUFFER, debugVerts.size() * sizeof(float), debugVerts.data(), GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(debugVerts.size() / 5));

        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);

        // Also log to console every second
        static float debugTimer = 0.0f;
        debugTimer += Core::Time::GetDeltaTime();

        if (debugTimer >= 1.0f)
        {
            Core::Logging::Log("[DEBUG] FPS: " + std::to_string(static_cast<int>(fps)) +
                               " | Frames: " + std::to_string(frames) +
                               " | Time: " + std::to_string(static_cast<int>(Core::Time::GetTimeSinceStart())) + "s");
            debugTimer = 0.0f;
        }
    }

    void RendererSystem::Shutdown()
    {
        Core::Logging::Log("[Renderer] Shutting down Renderer System...");

        if (mDebugVAO)
        {
            glDeleteVertexArrays(1, &mDebugVAO);
            mDebugVAO = 0;
        }
        if (mDebugVBO)
        {
            glDeleteBuffers(1, &mDebugVBO);
            mDebugVBO = 0;
        }
        if (mDebugShaderID)
        {
            glDeleteProgram(mDebugShaderID);
            mDebugShaderID = 0;
        }

        mInitialized = false;
    }

    RendererSystem &Get()
    {
        return gRenderer;
    }

} // namespace Renderer
