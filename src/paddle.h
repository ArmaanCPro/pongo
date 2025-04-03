#pragma once

namespace pongo
{
    class paddle
    {
    public:
        paddle(float x, float y, float width, float height, float speed);

        void move_up(float delta_time);
        void move_down(float delta_time);

        // Get position and dimensions in world coordinates
        [[nodiscard]] float getX() const { return x_; }
        [[nodiscard]] float getY() const { return y_; }
        [[nodiscard]] float getWidth() const { return width_; }
        [[nodiscard]] float getHeight() const { return height_; }

    private:
        // pos in world coords
        float x_, y_;
        // dimensions in world coords
        float width_, height_;
        // movement speed in world units per second
        float speed_;
    };
}
