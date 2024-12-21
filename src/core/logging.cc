// src/core/logging.cc
#include "logging.h"
#include <iostream>
#include <mutex>

namespace Core
{

    std::mutex logMutex;

    void Logging::Log(const std::string &message, LogLevel level)
    {
        std::lock_guard<std::mutex> guard(logMutex);
        switch (level)
        {
        case LogLevel::LOG:
            std::cout << "[LOG] " << message << std::endl;
            break;
        case LogLevel::WARN:
            std::cerr << "[WARN] " << message << std::endl;
            break;
        case LogLevel::ERROR:
            std::cerr << "[ERROR] " << message << std::endl;
            break;
        }
    }

} // namespace Core
