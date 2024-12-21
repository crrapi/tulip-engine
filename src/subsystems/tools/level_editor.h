// src/subsystems/tools/level_editor.h
#pragma once
#include <string>

namespace Tools
{

    class LevelEditor
    {
    public:
        LevelEditor();
        ~LevelEditor();

        bool Initialize();
        void Update(float deltaTime);
        void Shutdown();

        // Example method to load a level
        void LoadLevel(const std::string &levelPath);

    private:
        bool mInitialized;
    };

    // Global accessor
    LevelEditor &Get();

} // namespace Tools
