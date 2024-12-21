// src/subsystems/renderer/mesh.cc
#include "mesh.h"
#include "src/core/logging.h"
#include <glad/glad.h>

namespace Renderer
{

    Mesh::Mesh()
        : VAO(0), VBO(0), EBO(0), mLoaded(false)
    {
    }

    Mesh::~Mesh()
    {
        if (mLoaded)
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
    }

    bool Mesh::Load(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Vertex attributes (assuming position only for simplicity)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        mLoaded = true;
        Core::Logging::Log("[Mesh] Mesh loaded successfully.");
        return true;
    }

    void Mesh::Draw() const
    {
        if (!mLoaded)
        {
            Core::Logging::Log("[Mesh] Attempted to draw an unloaded mesh.", Core::LogLevel::WARN);
            return;
        }
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, /*count=*/6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

} // namespace Renderer
