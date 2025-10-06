// src/core/time.cc
#include "time.h"

namespace Core
{

  float Time::sDeltaTime = 0.0f;
  float Time::sTimeSinceStart = 0.0f;

  void Time::Initialize()
  {
    sDeltaTime = 0.0f;
    sTimeSinceStart = 0.0f;
  }

  void Time::Shutdown()
  {
    // No special shutdown logic required
  }

  void Time::Tick(float deltaTime)
  {
    sDeltaTime = deltaTime;
    sTimeSinceStart += deltaTime;
  }

  float Time::GetDeltaTime()
  {
    return sDeltaTime;
  }

  float Time::GetTimeSinceStart()
  {
    return sTimeSinceStart;
  }

} // namespace Core
