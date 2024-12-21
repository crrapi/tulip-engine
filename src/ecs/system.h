// src/ecs/system.h
#pragma once

namespace ECS
{

    // Base class for systems
    class System
    {
    public:
        virtual ~System() = default;
        virtual void Initialize() {}
        virtual void Update(float deltaTime) {}
        virtual void Shutdown() {}
    };

} // namespace ECS
