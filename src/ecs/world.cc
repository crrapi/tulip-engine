// src/ecs/world.cc
#include "world.h"
#include "src/core/logging.h"

namespace ECS
{

    EntityID World::sNextEntityID = 1;

    World &World::Get()
    {
        static World instance;
        return instance;
    }

    void World::Initialize()
    {
        Core::Logging::Log("[ECS] Initializing ECS World.");
        // Initialize all registered systems
        for (auto *system : mSystems)
        {
            system->Initialize();
        }
    }

    void World::Update(float deltaTime)
    {
        for (auto *system : mSystems)
        {
            system->Update(deltaTime);
        }
    }

    void World::Shutdown()
    {
        Core::Logging::Log("[ECS] Shutting down ECS World.");
        // Shutdown all systems
        for (auto *system : mSystems)
        {
            system->Shutdown();
        }
        mSystems.clear();
        mEntities.clear();
        sNextEntityID = 1;
    }

    Entity World::CreateEntity()
    {
        Entity entity(sNextEntityID++);
        mEntities.emplace_back(entity);
        Core::Logging::Log("[ECS] Created Entity ID: " + std::to_string(entity.id));
        return entity;
    }

    void World::DestroyEntity(Entity entity)
    {
        auto it = std::find_if(mEntities.begin(), mEntities.end(),
                               [&](const Entity &e)
                               { return e.id == entity.id; });
        if (it != mEntities.end())
        {
            mEntities.erase(it);
            Core::Logging::Log("[ECS] Destroyed Entity ID: " + std::to_string(entity.id));
        }
    }

    void World::RegisterSystem(System *system)
    {
        mSystems.emplace_back(system);
        Core::Logging::Log("[ECS] Registered a new System.");
    }

} // namespace ECS
