// src/resources/asset_loader.cc
#include "asset_loader.h"
#include "src/core/logging.h"

namespace AssetLoader
{

    template <typename T>
    std::shared_ptr<T> AssetLoader::Load(const std::string &path)
    {
        Core::Logging::Log("[AssetLoader] Loading asset from: " + path);
        // Implement actual loading logic based on type T
        // For demonstration, we return a new instance without actual loading
        return std::make_shared<T>();
    }

    // Explicit template instantiation for commonly used types
    template std::shared_ptr<MeshResource> AssetLoader::Load<MeshResource>(const std::string &path);
    template std::shared_ptr<TextureResource> AssetLoader::Load<TextureResource>(const std::string &path);

} // namespace AssetLoader
