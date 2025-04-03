#include "renderer.h"

#include "settings.h"

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
    }

    void renderer::add_paddle()
    {
        // 6 verts * 3 components
        for (int i = 0; i < 18; i++)
            vertices_.emplace_back(0.0f);

        glBindVertexArray(VAO_);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_DYNAMIC_DRAW);
    }

    void renderer::render_paddle(const paddle& p, shader& s)
    {
        s.use();

        float half_width = p.getWidth() / 2.0f;
        float half_height = p.getHeight() / 2.0f;

        glm::vec2 center_ndc = utility::world_to_ndc(p.getX(), p.getY());

        // calculate corners
        float left = center_ndc.x - (half_width / WORLD_WIDTH * 2.0f);
        float right = center_ndc.x + (half_width / WORLD_WIDTH * 2.0f);
        float top = center_ndc.y + (half_height / WORLD_HEIGHT * 2.0f);
        float bottom = center_ndc.y - (half_height / WORLD_HEIGHT * 2.0f);

        // Update paddle vertices
        float vertices[] = {
            // position
            left,  top,    0.0f,  // top left
            left,  bottom, 0.0f,  // bottom left
            right, bottom, 0.0f,  // bottom right

            left,  top,    0.0f,  // top left
            right, bottom, 0.0f,  // bottom right
            right, top,    0.0f   // top right
        };
        //for (auto x : vertices)
            //vertices_.emplace_back(x);

        glBindVertexArray(VAO_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
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
