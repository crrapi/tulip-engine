// src/subsystems/renderer/mesh.h
#pragma once
#include <vector>
#include <memory>

namespace Renderer
{

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        bool Load(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        void Draw() const;

    private:
        unsigned int VAO, VBO, EBO;
        bool mLoaded;
        int mIndexCount;
    };

} // namespace Renderer
