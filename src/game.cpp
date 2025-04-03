#include "game.h"

namespace pongo
{

    game::game(renderer& r, shader& s, window& w)
        :
        gfx(r),
        main_shader(s),
        win(w)
    {

    }

    void game::update_model()
    {
        if (win.get_key_state(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            win.set_should_close(true);
    }

    void game::draw_frame()
    {
        gfx.draw(main_shader);
    }
}
