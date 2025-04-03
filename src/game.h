#pragma once

#include "ball.h"
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

        paddle player_paddle;
        paddle enemy_paddle;
        ball game_ball;

        float last_frame_time;


        // game state
        int player_score = 0;
        int enemy_score = 0;
        bool ai_active = true;
        bool ball_active = true;

        void handle_collisions();
        void reset_ball();

        void update_enemy_ai(float delta_time);
    };
} // namespace pongo
