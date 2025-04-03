#pragma once

#include "renderer.h"
#include "shader.h"
#include "window.h"

namespace pongo
{
    class game
    {
    public:
        game(renderer& r, shader& s, window& w);

        void update_model();
        void draw_frame();

    private:
        renderer& gfx;
        shader& main_shader;
        window& win;
    };
} // namespace pongo
