// src/platform/window.h
#pragma once

namespace Platform
{

    class Window
    {
    public:
        static void Create(const char *title, int width, int height);
        static void Destroy();
    };

} // namespace Platform
