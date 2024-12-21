// src/subsystems/renderer/shader.cc
#include "shader.h"
#include "src/core/logging.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>

namespace Renderer
{

    Shader::Shader()
        : ID(0), mLoaded(false)
    {
    }

    Shader::~Shader()
    {
        if (ID != 0)
        {
            glDeleteProgram(ID);
        }
    }

    std::string Shader::ReadFile(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            Core::Logging::Log("[Shader] Failed to open shader file: " + path, Core::LogLevel::ERROR);
            return "";
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    bool Shader::CompileShader(const char *source, unsigned int type, unsigned int &shader)
    {
        shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // Check compilation
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Core::Logging::Log("[Shader] Shader compilation failed: " + std::string(infoLog), Core::LogLevel::ERROR);
            return false;
        }
        return true;
    }

    bool Shader::Load(const std::string &vertexPath, const std::string &fragmentPath)
    {
        std::string vertexCode = ReadFile(vertexPath);
        std::string fragmentCode = ReadFile(fragmentPath);

        if (vertexCode.empty() || fragmentCode.empty())
        {
            return false;
        }

        unsigned int vertexShader, fragmentShader;
        if (!CompileShader(vertexCode.c_str(), GL_VERTEX_SHADER, vertexShader))
        {
            return false;
        }
        if (!CompileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, fragmentShader))
        {
            return false;
        }

        // Link shaders
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // Check linking
        int success;
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            Core::Logging::Log("[Shader] Shader program linking failed: " + std::string(infoLog), Core::LogLevel::ERROR);
            return false;
        }

        // Delete shaders as they're linked now
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        mLoaded = true;
        Core::Logging::Log("[Shader] Shader program loaded successfully.");
        return true;
    }

    void Shader::Use() const
    {
        if (!mLoaded)
        {
            Core::Logging::Log("[Shader] Attempted to use an unloaded shader.", Core::LogLevel::WARN);
            return;
        }
        glUseProgram(ID);
    }

} // namespace Renderer
