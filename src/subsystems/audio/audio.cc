// src/subsystems/audio/audio.cc
#include "audio.h"
#include "src/core/logging.h"
#include <fmod_errors.h>

namespace Audio
{

    static AudioSystem gAudioSystem;

    AudioSystem::AudioSystem()
        : mInitialized(false), mSystem(nullptr), mSound(nullptr), mChannel(nullptr)
    {
    }

    AudioSystem::~AudioSystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool AudioSystem::Initialize()
    {
        FMOD_RESULT result;

        // Create FMOD system
        result = FMOD::System_Create(&mSystem);
        if (result != FMOD_OK)
        {
            Core::Logging::Log("[Audio] FMOD::System_Create failed.", Core::LogLevel::ERROR);
            return false;
        }

        // Initialize FMOD system
        result = mSystem->init(512, FMOD_INIT_NORMAL, 0);
        if (result != FMOD_OK)
        {
            Core::Logging::Log("[Audio] FMOD system initialization failed.", Core::LogLevel::ERROR);
            return false;
        }

        mInitialized = true;
        Core::Logging::Log("[Audio] FMOD initialized successfully.");
        return true;
    }

    void AudioSystem::Update()
    {
        if (!mInitialized || !mSystem)
            return;

        // Update FMOD system
        mSystem->update();
    }

    void AudioSystem::Shutdown()
    {
        Core::Logging::Log("[Audio] Shutting down FMOD...");

        if (mSound)
        {
            mSound->release();
            mSound = nullptr;
        }

        if (mSystem)
        {
            mSystem->close();
            mSystem->release();
            mSystem = nullptr;
        }

        mInitialized = false;
        Core::Logging::Log("[Audio] FMOD shutdown complete.");
    }

    void AudioSystem::PlaySound(const std::string &soundPath)
    {
        if (!mInitialized || !mSystem)
            return;

        if (mSound)
        {
            mSound->release();
            mSound = nullptr;
        }

        FMOD_RESULT result = mSystem->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &mSound);
        if (result != FMOD_OK)
        {
            Core::Logging::Log("[Audio] Failed to load sound: " + soundPath, Core::LogLevel::ERROR);
            return;
        }

        result = mSystem->playSound(mSound, 0, false, &mChannel);
        if (result != FMOD_OK)
        {
            Core::Logging::Log("[Audio] Failed to play sound: " + soundPath, Core::LogLevel::ERROR);
            return;
        }

        Core::Logging::Log("[Audio] Playing sound: " + soundPath);
    }

    AudioSystem &Get()
    {
        return gAudioSystem;
    }

} // namespace Audio
