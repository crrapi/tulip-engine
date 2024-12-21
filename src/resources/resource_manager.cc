// src/resources/resource_manager.cc
#include "resource_manager.h"
#include "asset_loader.h"
#include "src/core/logging.h"

namespace Resources
{

    static Manager gResourceManager;

    Manager &Manager::Get()
    {
        return gResourceManager;
    }

    void Manager::Initialize()
    {
        Core::Logging::Log("[Resources] Initializing Resource Manager.");
    }

    void Manager::Shutdown()
    {
        Core::Logging::Log("[Resources] Shutting down Resource Manager.");
        mResources.clear();
    }

    template <typename T>
    std::shared_ptr<T> Manager::Load(const std::string &path)
    {
        // Check if the resource is already loaded
        auto it = mResources.find(path);
        if (it != mResources.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }

        // Load the resource using AssetLoader
        auto resource = AssetLoader::Load<T>(path);
        if (resource)
        {
            mResources[path] = resource;
            Core::Logging::Log("[Resources] Loaded resource: " + path);
        }
        else
        {
            Core::Logging::Log("[Resources] Failed to load resource: " + path, Core::LogLevel::ERROR);
        }
        return resource;
    }

    // Explicit template instantiation for commonly used types
    template std::shared_ptr<AssetLoader::MeshResource> Manager::Load<AssetLoader::MeshResource>(const std::string &);
    template std::shared_ptr<AssetLoader::TextureResource> Manager::Load<AssetLoader::TextureResource>(const std::string &);

} // namespace Resources
