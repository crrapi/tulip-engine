// src/subsystems/audio/audio.h
#pragma once
#include <fmod.hpp>
#include <string>

namespace Audio
{

    class AudioSystem
    {
    public:
        AudioSystem();
        ~AudioSystem();

        bool Initialize();
        void Update();
        void Shutdown();

        // Example method to play a sound
        void PlaySound(const std::string &soundPath);

    private:
        bool mInitialized;
        FMOD::System *mSystem;
        FMOD::Sound *mSound;
        FMOD::Channel *mChannel;
    };

    // Global accessor
    AudioSystem &Get();

} // namespace Audio
