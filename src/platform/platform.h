// src/platform/platform.h
#pragma once

namespace Platform
{

    void Initialize();
    void Shutdown();

    void CreateMainWindow(const char *title, int width, int height);
    void DestroyMainWindow();

} // namespace Platform
