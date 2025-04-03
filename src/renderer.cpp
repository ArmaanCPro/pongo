#include "renderer.h"

namespace pongo
{
    renderer::renderer()
    {
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);

        glBindVertexArray(VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f,  -0.5f, 0.0f, // right
            0.0f,  0.5f,  0.0f  // top
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void renderer::draw(shader s)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s.use();

        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
} // namespace pongo
