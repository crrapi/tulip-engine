// src/subsystems/renderer/material.cc
#include "material.h"
#include "src/core/logging.h"

namespace Renderer
{

    Material::Material()
        : mLoaded(false)
    {
    }

    Material::~Material()
    {
        // Shader will be automatically deleted via shared_ptr
    }

    bool Material::Load(const std::string &vertexPath, const std::string &fragmentPath)
    {
        mShader = std::make_shared<Shader>();
        if (!mShader->Load(vertexPath, fragmentPath))
        {
            Core::Logging::Log("[Material] Failed to load shader.", Core::LogLevel::ERROR);
            return false;
        }
        mLoaded = true;
        Core::Logging::Log("[Material] Material loaded successfully.");
        return true;
    }

    void Material::Apply() const
    {
        if (!mLoaded || !mShader)
        {
            Core::Logging::Log("[Material] Attempted to apply an unloaded material.", Core::LogLevel::WARN);
            return;
        }
        mShader->Use();
    }

} // namespace Renderer
