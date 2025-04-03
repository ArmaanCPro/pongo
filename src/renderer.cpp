#include "renderer.h"

#include "settings.h"

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
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);

        glBindVertexArray(VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

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
        vertices_.clear();  // Clear any existing vertices
        for (float vertex : paddleVerts)
        {
            vertices_.push_back(vertex);
        }

        glBindVertexArray(VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_DYNAMIC_DRAW);

    }

    void renderer::render_paddle(const paddle& p, shader& s)
    {
        s.use();

        // Create model matrix for the paddle
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(p.getX(), p.getY(), 0.0f));
        model = glm::scale(model, glm::vec3(p.getWidth(), p.getHeight(), 1.0f));
        s.SetMat4("model", model);

        // use cached projection matrix
        s.SetMat4("projection", projection_matrix_);

        s.SetMat4("view", glm::mat4(1.0f));

        // Draw standard paddle geometry (centered at origin)
        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void renderer::draw_all_verts(shader s)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s.use();

        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
} // namespace pongo
