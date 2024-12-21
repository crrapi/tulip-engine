// src/ecs/entity.h
#pragma once
#include <cstdint>

namespace ECS
{

    using EntityID = uint32_t;

    class Entity
    {
    public:
        EntityID id;
        explicit Entity(EntityID eid) : id(eid) {}
    };

} // namespace ECS
