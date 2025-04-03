#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "window.h"
#include "renderer.h"
#include "shader.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    pongo::window& window = pongo::window::get_instance();
    window.initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Pongo");

    pongo::renderer renderer;

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
        renderer.draw(shader);

        window.swap_and_poll();
    }

    window.shutdown();
    return 0;
}
