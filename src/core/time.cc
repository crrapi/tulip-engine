// src/core/time.cc
#include "time.h"

namespace Core
{

    float Time::sDeltaTime = 0.0f;
    float Time::sTimeSinceStart = 0.0f;
    static int sFrameCount = 0;
    static float sFPSTimer = 0.0f;
    static float sCurrentFPS = 0.0f;
    static int sFramesThisSecond = 0;

    void Time::Initialize()
    {
        sDeltaTime = 0.0f;
        sTimeSinceStart = 0.0f;
        sFrameCount = 0;
        sFPSTimer = 0.0f;
        sCurrentFPS = 0.0f;
        sFramesThisSecond = 0;
    }

  void Time::Shutdown()
  {
    // No special shutdown logic required
  }

    void Time::Tick(float deltaTime)
    {
        sDeltaTime = deltaTime;
        sTimeSinceStart += deltaTime;
        sFrameCount++;
        sFramesThisSecond++;
        
        sFPSTimer += deltaTime;
        if (sFPSTimer >= 1.0f)
        {
            sCurrentFPS = static_cast<float>(sFramesThisSecond) / sFPSTimer;
            sFramesThisSecond = 0;
            sFPSTimer = 0.0f;
        }
    }

    float Time::GetDeltaTime()
    {
        return sDeltaTime;
    }

    float Time::GetTimeSinceStart()
    {
        return sTimeSinceStart;
    }

    float Time::GetFPS()
    {
        return sCurrentFPS;
    }

    int Time::GetFrameCount()
    {
        return sFrameCount;
    }

} // namespace Core
