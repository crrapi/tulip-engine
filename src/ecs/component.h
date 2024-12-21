// src/ecs/component.h
#pragma once

namespace ECS
{

    // Base class for components
    struct Component
    {
        virtual ~Component() = default;
    };

} // namespace ECS
