#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "game.h"

#include "settings.h"

int main()
{
    pongo::window& window = pongo::window::get_instance();
    window.initialize(pongo::SCREEN_WIDTH, pongo::SCREEN_HEIGHT, "Pongo");

    pongo::renderer renderer;

    shader shader("vertex.glsl", "fragment.glsl");

    pongo::game game(renderer, shader, window);

    while (!window.should_close())
    {
        game.update_model();

        game.draw_frame();

        window.swap_and_poll();
    }

    window.shutdown();
    return 0;
}
