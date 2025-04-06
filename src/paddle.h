#pragma once

#include "renderable_component.h"
#include "material.h"
#include "mesh.h"
#include <memory>

namespace pongo
{
    class paddle
    {
    public:
        paddle(float x, float y, float width, float height, float speed, const glm::vec4& color = glm::vec4(1.0f));

        void move_up(float delta_time);
        void move_down(float delta_time);

        // Get position and dimensions in world coordinates
        [[nodiscard]] float getX() const { return x_; }
        [[nodiscard]] float getY() const { return y_; }
        [[nodiscard]] float getWidth() const { return width_; }
        [[nodiscard]] float getHeight() const { return height_; }

        [[nodiscard]] const renderable_component& get_renderable() const;

        void update_transform() const;

    private:
        // pos in world coords
        float x_, y_;
        // dimensions in world coords
        float width_, height_;
        // movement speed in world units per second
        float speed_;

        std::unique_ptr<renderable_component> renderable_ = nullptr;
    };
}
