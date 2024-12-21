// src/resources/resource_manager.h
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "asset_loader.h"

namespace Resources
{

    class ResourceBase
    {
    public:
        virtual ~ResourceBase() = default;
    };

    class Manager
    {
    public:
        static Manager &Get();

        void Initialize();
        void Shutdown();

        template <typename T>
        std::shared_ptr<T> Load(const std::string &path);

    private:
        Manager() = default;
        ~Manager() = default;

        std::unordered_map<std::string, std::shared_ptr<ResourceBase>> mResources;
    };

} // namespace Resources
