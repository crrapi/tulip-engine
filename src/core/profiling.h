// src/core/profiling.h
#pragma once

namespace Core
{

    class Profiling
    {
    public:
        static void BeginSample(const char *name);
        static void EndSample();
    };

} // namespace Core
