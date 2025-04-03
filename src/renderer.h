#pragma once

#include "ball.h"

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
        void add_ball();

        void begin_scene(shader& s);
        void render_paddle(const paddle& p, shader& s, const glm::vec4& color = glm::vec4(1.0f));
        void render_ball(const ball& b, shader& s, const glm::vec4& color = glm::vec4(1.0f));
    private:
        GLuint paddle_VAO_ = 0, paddle_VBO_ = 0;
        std::vector<float> paddle_vertices_ = { 0.0f };
        GLuint ball_VAO_ = 0, ball_VBO_ = 0;
        std::vector<float> ball_vertices_ = { 0.0f };
        int ball_segments_ = 32;
        glm::mat4 projection_matrix_;
    };
}
