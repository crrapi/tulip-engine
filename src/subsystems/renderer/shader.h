// src/subsystems/renderer/shader.h
#pragma once
#include <string>

namespace Renderer
{

    class Shader
    {
    public:
        Shader();
        ~Shader();

        bool Load(const std::string &vertexPath, const std::string &fragmentPath);
        void Use() const;

    private:
        unsigned int ID;
        bool mLoaded;

        std::string ReadFile(const std::string &path);
        bool CompileShader(const char *source, unsigned int type, unsigned int &shader);
    };

} // namespace Renderer
