#include "shader.h"

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    pongo::window& window = pongo::window::get_instance();
    window.initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Pongo");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f,  -0.5f, 0.0f, // right
        0.0f,  0.5f,  0.0f  // top
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader shader("vertex.glsl", "fragment.glsl");

    shader.use();

    auto input_handler = [](pongo::window& window)
    {
        if (window.get_key_state(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.set_should_close(true);
    };

    while (!window.should_close())
    {
        // input
        input_handler(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_and_poll();
    }

    window.shutdown();
    return 0;
}
