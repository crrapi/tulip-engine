// src/core/profiling.cc
#include "profiling.h"
#include "logging.h"

namespace Core
{

    void Profiling::BeginSample(const char *name)
    {
        Logging::Log(std::string("[Profiling] Begin sample: ") + name);
        // Integrate with a profiling tool or library
    }

    void Profiling::EndSample()
    {
        Logging::Log("[Profiling] End sample.");
        // Integrate with a profiling tool or library
    }

} // namespace Core
