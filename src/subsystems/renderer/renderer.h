// src/subsystems/renderer/renderer.h
#pragma once

namespace Renderer
{

    class RendererSystem
    {
    public:
        RendererSystem();
        ~RendererSystem();

        void Initialize();
        void RenderFrame();
        void Shutdown();

    private:
        bool mInitialized;
        bool mSampleSetupDone;
        float mRotation;
    };

    // Global accessor
    RendererSystem &Get();

} // namespace Renderer
