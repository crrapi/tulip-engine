// src/core/memory.h
#pragma once
#include <cstddef>

namespace Core
{

    class Memory
    {
    public:
        static void Initialize();
        static void Shutdown();

        // Custom memory allocation methods
        static void *Alloc(std::size_t size);
        static void Free(void *ptr);
    };

} // namespace Core
