// src/subsystems/renderer/scene.h
#pragma once
#include <vector>
#include <memory>
#include "mesh.h"
#include "material.h"

namespace Renderer
{

    class Scene
    {
    public:
        static Scene &Get();

        void AddMesh(const std::shared_ptr<Mesh> &mesh);
        void AddMaterial(const std::shared_ptr<Material> &material);
        void SetDefaultMaterial(const std::shared_ptr<Material> &material);
        void Render();
        void SetMaterialFloat(const std::string &name, float value);

    private:
        Scene() = default;
        ~Scene() = default;

        std::vector<std::shared_ptr<Mesh>> mMeshes;
        std::vector<std::shared_ptr<Material>> mMaterials;
        std::shared_ptr<Material> mDefaultMaterial;
    };

} // namespace Renderer
