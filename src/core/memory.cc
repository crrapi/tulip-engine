// src/core/memory.cc
#include "memory.h"
#include "logging.h"
#include <cstdlib>

namespace Core
{

    void Memory::Initialize()
    {
        Logging::Log("[Memory] Memory system initialized.");
        // Initialize custom memory pools or allocators if needed
    }

    void Memory::Shutdown()
    {
        Logging::Log("[Memory] Memory system shutting down.");
        // Cleanup memory pools or custom allocators
    }

    void *Memory::Alloc(std::size_t size)
    {
        return std::malloc(size);
    }

    void Memory::Free(void *ptr)
    {
        std::free(ptr);
    }

} // namespace Core
