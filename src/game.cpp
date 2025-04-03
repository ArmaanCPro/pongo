#include "game.h"

namespace pongo
{

    game::game(renderer& r, shader& s, window& w)
        :
        gfx(r),
        main_shader(s),
        win(w),
        player_paddle(10.0f, 50.0f, 2.5f, 15.0f, 30.0f),
        enemy_paddle(90.0f, 50.0f, 2.5f, 15.0f, 30.0f),
        last_frame_time((float)glfwGetTime())
    {
        gfx.add_paddle();
    }

    void game::update_model()
    {
        // calculate delta time
        float current_time = (float)glfwGetTime();
        float delta_time = current_time - last_frame_time;
        last_frame_time = current_time;

        if (win.get_key_state(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            win.set_should_close(true);

        if (win.get_key_state(GLFW_KEY_W) == GLFW_PRESS)
            player_paddle.move_up(delta_time);
        if (win.get_key_state(GLFW_KEY_S) == GLFW_PRESS)
            player_paddle.move_down(delta_time);

        // Player 2 controls or simple AI
        // Option 1: Player 2 controls with arrow keys
        if (win.get_key_state(GLFW_KEY_UP) == GLFW_PRESS)
            enemy_paddle.move_up(delta_time);
        if (win.get_key_state(GLFW_KEY_DOWN) == GLFW_PRESS)
            enemy_paddle.move_down(delta_time);
    }

    void game::draw_frame()
    {
        // Clear the screen. We can't do this in the renderer because it would clear the screen each time a different paddle is rendered
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gfx.render_paddle(player_paddle, main_shader);
        gfx.render_paddle(enemy_paddle, main_shader);
        //gfx.draw_all_verts(main_shader);
    }
}
