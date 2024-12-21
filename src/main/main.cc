// src/main/main.cc
#include "src/engine/engine.h"
#include "src/core/logging.h"

int main(int argc, char **argv)
{
    Core::Logging::Log("[MAIN] Launching Tulip Engine...");

    // Instantiate and initialize the game engine
    Engine::GameEngine engine;
    engine.Initialize();

    // Main game loop
    bool running = true;
    while (running)
    {
        engine.Update(1.0f / 60.0f); // Assuming 60 FPS

        // Example exit condition
        if (Input::Get().ShouldQuit())
        {
            running = false;
        }
    }

    // Shutdown the engine
    engine.Shutdown();
    Core::Logging::Log("[MAIN] Tulip Engine has shut down.");

    return 0;
}
