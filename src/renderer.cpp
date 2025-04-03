#include "renderer.h"

#include "settings.h"

#include <glm/common.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace utility
{
    glm::vec2 world_to_ndc(float wx, float wy)
    {
        return glm::vec2(2.0f * wx / pongo::WORLD_WIDTH - 1.0f, 1.0f - 2.0f * wy / pongo::WORLD_HEIGHT);
    }
}

namespace pongo
{
    renderer::renderer()
    {
        glGenVertexArrays(1, &paddle_VAO_);
        glGenBuffers(1, &paddle_VBO_);

        glBindVertexArray(paddle_VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, paddle_VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * paddle_vertices_.size(), paddle_vertices_.data(), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        glGenVertexArrays(1, &ball_VAO_);
        glGenBuffers(1, &ball_VBO_);

        glBindVertexArray(ball_VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, ball_VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ball_vertices_.size(), ball_vertices_.data(), GL_STATIC_DRAW);

        // world to ndc projection matrix
        projection_matrix_ = glm::ortho(0.0f, WORLD_WIDTH, 0.0f, WORLD_HEIGHT, -1.0f, 1.0f);
    }

    void renderer::add_paddle()
    {
        // A simple rectangle centered at origin
        float paddleVerts[] = {
            // Position (x, y, z)
            -0.5f,  0.5f, 0.0f,  // top left
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right

            -0.5f,  0.5f, 0.0f,  // top left
             0.5f, -0.5f, 0.0f,  // bottom right
             0.5f,  0.5f, 0.0f   // top right
        };

        // Add to vertices vector
        paddle_vertices_.clear();  // Clear any existing vertices
        for (float vertex : paddleVerts)
        {
            paddle_vertices_.push_back(vertex);
        }

        glBindVertexArray(paddle_VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, paddle_VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * paddle_vertices_.size(), paddle_vertices_.data(), GL_DYNAMIC_DRAW);

    }

    void renderer::add_ball()
    {
        // Generate a circle approximation using triangles
        ball_vertices_.clear();

        // Center vertex
        ball_vertices_.push_back(0.0f); // x
        ball_vertices_.push_back(0.0f); // y
        ball_vertices_.push_back(0.0f); // z

        // Add vertices for each segment
        for (int i = 0; i <= ball_segments_; i++)
        {
            float angle = 2.0f * glm::pi<float>() * i / ball_segments_;
            float x = std::cos(angle);
            float y = std::sin(angle);

            ball_vertices_.push_back(x); // x
            ball_vertices_.push_back(y); // y
            ball_vertices_.push_back(0.0f); // z
        }

        // Create and bind VAO/VBO for the ball
        glGenVertexArrays(1, &ball_VAO_);
        glGenBuffers(1, &ball_VBO_);

        glBindVertexArray(ball_VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, ball_VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ball_vertices_.size(), ball_vertices_.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void renderer::begin_scene(shader& s)
    {
        s.use();

        s.SetMat4("projection", projection_matrix_);

        s.SetMat4("view", glm::mat4(1.0f));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void renderer::render_paddle(const paddle& p, shader& s, const glm::vec4& color)
    {
        // Create model matrix for the paddle
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(p.getX(), p.getY(), 0.0f));
        model = glm::scale(model, glm::vec3(p.getWidth(), p.getHeight(), 1.0f));
        s.SetMat4("model", model);

        // set custom color uniform for frag shader
        s.SetVec4("u_Color", color);

        // Draw standard paddle geometry (centered at origin)
        glBindVertexArray(paddle_VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void renderer::render_ball(const ball& b, shader& s, const glm::vec4& color)
    {
        // Create model matrix for the ball
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(b.getX(), b.getY(), 0.0f));
        model = glm::scale(model, glm::vec3(b.getRadius(), b.getRadius(), 1.0f));
        s.SetMat4("model", model);

        // set custom color uniform for frag shader
        s.SetVec4("u_Color", color);

        // Draw standard ball geometry (centered at origin)
        glBindVertexArray(ball_VAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, ball_segments_ + 2);
    }
} // namespace pongo
