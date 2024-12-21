// src/core/logging.h
#pragma once
#include <string>

namespace Core
{

    enum class LogLevel
    {
        LOG,
        WARN,
        ERROR
    };

    class Logging
    {
    public:
        static void Log(const std::string &message, LogLevel level = LogLevel::LOG);
    };

} // namespace Core
