#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"

namespace pongo
{
    class renderer
    {
    public:
        renderer();

        void draw(shader s);
    private:
        GLuint VAO_, VBO_;
    };
}
