// src/ecs/world.h
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "entity.h"
#include "system.h"

namespace ECS
{

    class World
    {
    public:
        static World &Get();

        void Initialize();
        void Update(float deltaTime);
        void Shutdown();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        // Register a system
        void RegisterSystem(System *system);

    private:
        World() = default;
        ~World() = default;

        std::vector<Entity> mEntities;
        std::vector<System *> mSystems;
        static EntityID sNextEntityID;
    };

} // namespace ECS
