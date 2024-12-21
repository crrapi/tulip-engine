// src/subsystems/renderer/scene.cc
#include "scene.h"
#include "src/core/logging.h"

namespace Renderer
{

    Scene &Scene::Get()
    {
        static Scene instance;
        return instance;
    }

    void Scene::AddMesh(const std::shared_ptr<Mesh> &mesh)
    {
        mMeshes.emplace_back(mesh);
        Core::Logging::Log("[Scene] Mesh added to scene.");
    }

    void Scene::AddMaterial(const std::shared_ptr<Material> &material)
    {
        mMaterials.emplace_back(material);
        Core::Logging::Log("[Scene] Material added to scene.");
    }

    void Scene::Render()
    {
        Core::Logging::Log("[Scene] Rendering Scene with " + std::to_string(mMeshes.size()) + " meshes.");
        for (const auto &mesh : mMeshes)
        {
            mesh->Draw();
        }
    }

} // namespace Renderer
