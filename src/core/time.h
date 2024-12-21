// src/core/time.h
#pragma once

namespace Core
{

    class Time
    {
    public:
        static void Initialize();
        static void Shutdown();
        static void Tick(float deltaTime);
        static float GetDeltaTime();
        static float GetTimeSinceStart();

    private:
        static float sDeltaTime;
        static float sTimeSinceStart;
    };

} // namespace Core
