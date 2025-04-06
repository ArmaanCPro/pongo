#pragma once

#include "paddle.h"
#include "renderable_component.h"
#include "mesh.h"
#include "material.h"

namespace pongo
{
    class ball
    {
    public:
        ball(float x, float y, float vx, float vy, float radius, const glm::vec4& color = glm::vec4(1.0f));
        ~ball();

        void move(float delta_time);
        void bounce_x();
        void bounce_y();
        void reset(float x, float y, float vx, float vy);
        void accelerate(float factor);

        // Add collision detection for paddles and screen bounds
        [[nodiscard]] bool collides_with_paddle(const paddle& p) const;
        void handle_paddle_collision(const paddle& p);
        [[nodiscard]] bool is_out_of_bounds_x(float min_x, float max_x) const;
        [[nodiscard]] bool is_out_of_bounds_y(float min_y, float max_y) const;

        // Getters and setters
        [[nodiscard]] float getX() const { return x_; }
        [[nodiscard]] float getY() const { return y_; }
        [[nodiscard]] float getVX() const { return vx_; }
        [[nodiscard]] float getVY() const { return vy_; }
        [[nodiscard]] float getRadius() const { return radius_; }

        void setVX(float vx) { vx_ = vx; }
        void setVY(float vy) { vy_ = vy; }

        // needed for rendering
        [[nodiscard]] const renderable_component& get_renderable() const;

    private:
        float x_, y_;
        float vx_, vy_;
        float radius_;

        renderable_component* renderable_ = nullptr;

        void update_transform();
    };
}
