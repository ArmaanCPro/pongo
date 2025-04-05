#pragma once
#include <vector>
#include <glad/glad.h>

namespace pongo
{
    class mesh
    {
    public:
        explicit mesh(const std::vector<float>& vertices);
        ~mesh();

        void bind() const;
        void unbind() const;
        void draw() const;

    private:
        GLuint VAO_ = 0, VBO_ = 0;
        uint64_t vertex_count_ = 0;
    };
}
