// src/resources/asset_loader.h
#pragma once
#include <memory>
#include <string>
#include "resource_manager.h"

namespace AssetLoader
{

    class MeshResource : public Resources::ResourceBase
    {
    public:
        // Mesh data and methods
    };

    class TextureResource : public Resources::ResourceBase
    {
    public:
        // Texture data and methods
    };

    class AssetLoader
    {
    public:
        template <typename T>
        static std::shared_ptr<T> Load(const std::string &path);
    };

} // namespace AssetLoader
