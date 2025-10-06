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

    void Scene::SetDefaultMaterial(const std::shared_ptr<Material> &material)
    {
        mDefaultMaterial = material;
        Core::Logging::Log("[Scene] Default material set.");
    }

    void Scene::Render()
    {
        if (mDefaultMaterial)
        {
            mDefaultMaterial->Apply();
        }
        for (const auto &mesh : mMeshes)
        {
            mesh->Draw();
        }
    }

    void Scene::SetMaterialFloat(const std::string &name, float value)
    {
        if (mDefaultMaterial)
        {
            mDefaultMaterial->SetFloat(name, value);
        }
    }

} // namespace Renderer
