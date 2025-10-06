// src/subsystems/renderer/material.h
#pragma once
#include <string>
#include <memory>
#include "shader.h"
#include "mesh.h"

namespace Renderer
{

    class Material
    {
    public:
        Material();
        ~Material();

        bool Load(const std::string &vertexPath, const std::string &fragmentPath);
        bool LoadFromSource(const std::string &vertexSource, const std::string &fragmentSource);
        void Apply() const;
        void SetFloat(const std::string &name, float value) const;

    private:
        std::shared_ptr<Shader> mShader;
        bool mLoaded;
    };

} // namespace Renderer
