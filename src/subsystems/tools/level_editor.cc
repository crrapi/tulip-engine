// src/subsystems/tools/level_editor.cc
#include "level_editor.h"
#include "src/core/logging.h"
#include "src/subsystems/renderer/renderer.h"

namespace Tools
{

    static LevelEditor gLevelEditor;

    LevelEditor::LevelEditor()
        : mInitialized(false)
    {
    }

    LevelEditor::~LevelEditor()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool LevelEditor::Initialize()
    {
        Core::Logging::Log("[LevelEditor] Initializing Level Editor...");
        // Initialize level editor components, UI, etc.
        mInitialized = true;
        Core::Logging::Log("[LevelEditor] Level Editor initialized successfully.");
        return true;
    }

    void LevelEditor::Update(float deltaTime)
    {
        if (!mInitialized)
            return;

        // Update level editor UI, handle user input, etc.
        Core::Logging::Log("[LevelEditor] Level Editor updated.");
    }

    void LevelEditor::Shutdown()
    {
        Core::Logging::Log("[LevelEditor] Shutting down Level Editor...");
        // Cleanup level editor components
        mInitialized = false;
        Core::Logging::Log("[LevelEditor] Level Editor shutdown complete.");
    }

    void LevelEditor::LoadLevel(const std::string &levelPath)
    {
        Core::Logging::Log("[LevelEditor] Loading level from: " + levelPath);
        // Implement level loading logic
    }

    LevelEditor &Get()
    {
        return gLevelEditor;
    }

} // namespace Tools
