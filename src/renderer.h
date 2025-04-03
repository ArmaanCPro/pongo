#pragma once

#include <vector>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "paddle.h"

namespace pongo
{
    class renderer
    {
    public:
        renderer();

        void add_paddle();

        void begin_scene(shader& s);
        void render_paddle(const paddle& p, shader& s);

        void draw_all_verts(shader s);
    private:
        GLuint VAO_ = 0, VBO_ = 0;
        std::vector<float> vertices_ = { 0.0f };
        glm::mat4 projection_matrix_;
    };
}
