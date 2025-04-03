#pragma once
#include "paddle.h"

namespace pongo
{
    class ball
    {
    public:
        ball(float x, float y, float vx, float vy, float radius);

        void move(float delta_time);
        void bounce_x();
        void bounce_y();
        void reset(float x, float y, float vx, float vy);
        void accelerate(float factor);

        // Add collision detection for paddles and screen bounds
        [[nodiscard]] bool collides_with_paddle(const paddle& p) const;
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

    private:
        float x_, y_;
        float vx_, vy_;
        float radius_;
    };
}
