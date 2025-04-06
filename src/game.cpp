#include "game.h"

#include "settings.h"

namespace pongo
{
    game::game(renderer& r, shader& s, window& w)
        : gfx(r), main_shader(s), win(w), player_paddle(10.0f, 50.0f, 1.5f, 15.0f, 40.0f),
          enemy_paddle(90.0f, 50.0f, 1.5f, 15.0f, 35.0f, glm::vec4(1.0f, 0.1f, 1.0f, 1.0f)),
          game_ball(50.0f, 50.0f, 40.0f, 30.0f, 2.0f, glm::vec4(0.1f, 1.0f, 0.1f, 1.0f)),
          last_frame_time((float)glfwGetTime())
    {
        std::cout << "Play against ai? y/n" << std::endl;
        std::string input;
        std::cin >> input;
        ai_active = (input == "y");
        std::cout << '\n';
        std::cout << "P1 Controls w/ arrow keys\n";
        if (!ai_active)
            std::cout << "P2 Controls w/ arrow keys" << std::endl;
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

        if (ai_active)
            update_enemy_ai(delta_time);
        else if (win.get_key_state(GLFW_KEY_UP) == GLFW_PRESS)
            enemy_paddle.move_up(delta_time);
        else if (win.get_key_state(GLFW_KEY_DOWN) == GLFW_PRESS)
            enemy_paddle.move_down(delta_time);

        // Update ball position
        if (ball_active)
            game_ball.move(delta_time);

        // Handle collisions
        handle_collisions();
    }

    void game::draw_frame()
    {
        // Clear screen
        gfx.clear();

        // Create orthographic projection with Y-axis flipped
        // (0,0) is bottom-left, (WORLD_WIDTH, WORLD_HEIGHT) is top-right
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(pongo::WORLD_WIDTH), 0.0f,
                                          static_cast<float>(pongo::WORLD_HEIGHT), -1.0f, 1.0f);

        // Identity view matrix for 2D
        glm::mat4 view = glm::mat4(1.0f);

        // Begin scene
        gfx.begin_scene();

        // Submit all renderables
        gfx.submit(player_paddle);
        gfx.submit(enemy_paddle);
        gfx.submit(game_ball);

        // Set uniforms before end_scene
        main_shader.use();
        main_shader.SetMat4("u_Projection", projection);
        main_shader.SetMat4("u_View", view);

        // End scene and render everything
        gfx.end_scene(main_shader);
    }

    void game::handle_collisions()
    {
        // ball-paddle collisions
        if (game_ball.collides_with_paddle(player_paddle))
        {
            game_ball.handle_paddle_collision(player_paddle);
        }
        else if (game_ball.collides_with_paddle(enemy_paddle))
        {
            game_ball.handle_paddle_collision(enemy_paddle);
        }

        // ball-wall (top/bottom)
        if (game_ball.is_out_of_bounds_y(0.0f, WORLD_HEIGHT))
        {
            game_ball.bounce_y();
        }

        // scoring (left/right walls)
        if (game_ball.getX() - game_ball.getRadius() < 0.0f)
        {
            // enemy scores
            enemy_score++;
            reset_ball();
        }
        else if (game_ball.getX() + game_ball.getRadius() > WORLD_WIDTH)
        {
            // player scores
            player_score++;
            reset_ball();
        }
    }

    void game::reset_ball()
    {
        ball_active = false;

#ifdef PL_WINDOWS
        system("cls");
#else
        system("clear");
#endif
        std::cout << "P1 Score: " << player_score << std::endl;
        std::cout << "P2 Score: " << enemy_score << std::endl;

        // reset ball to center with a random vertical velocity
        float random_vy = 20.0f + (rand() % 40) - 20.0f;

        float vx = (rand() % 2 == 0) ? 40.0f : -40.0f;

        game_ball.reset(WORLD_WIDTH / 2, WORLD_HEIGHT / 2, vx, random_vy);

        // TODO add small delay before ball becomes active again
        ball_active = true;
    }

    void game::update_enemy_ai(float delta_time)
    {
        // Basic AI: follow the ball with some reaction delay
        float target_y = game_ball.getY();
        float current_y = enemy_paddle.getY();

        // Add some "reaction time" - only move when ball is moving toward the AI
        if (game_ball.getVX() > 0 && game_ball.getX() > WORLD_WIDTH / 2)
        {
            // Move toward the ball's y position
            if (target_y > current_y + enemy_paddle.getHeight() * 0.2f)
                enemy_paddle.move_up(delta_time);
            else if (target_y < current_y - enemy_paddle.getHeight() * 0.2f)
                enemy_paddle.move_down(delta_time);
        }

        // Optional: add some difficulty scaling
        // Add randomness to make it beatable
        // Adjust speed based on score difference
    }
} // namespace pongo
