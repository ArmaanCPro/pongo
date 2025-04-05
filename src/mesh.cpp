#include "mesh.h"

namespace pongo
{
    mesh::mesh(const std::vector<float>& vertices)
        :
        vertex_count_(vertices.size() / 5)
    {
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);

        glBindVertexArray(VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

        // pos attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // tex coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    mesh::~mesh()
    {
        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);
    }

    void mesh::bind() const
    {
        glBindVertexArray(VAO_);
    }

    void mesh::unbind() const
    {
        glBindVertexArray(0);
    }

    void mesh::draw() const
    {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(vertex_count_));
    }
}
