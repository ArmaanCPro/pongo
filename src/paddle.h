#pragma once

#include "renderable.h"
#include "material.h"
#include "mesh.h"

namespace pongo
{
    class paddle : public renderable
    {
    public:
        paddle(float x, float y, float width, float height, float speed, const glm::vec4& color = glm::vec4(1.0f));
        ~paddle() override;

        void move_up(float delta_time);
        void move_down(float delta_time);

        // Get position and dimensions in world coordinates
        [[nodiscard]] float getX() const { return x_; }
        [[nodiscard]] float getY() const { return y_; }
        [[nodiscard]] float getWidth() const { return width_; }
        [[nodiscard]] float getHeight() const { return height_; }

        // renderable interface implementation
        [[nodiscard]] mesh* get_mesh() const override;
        [[nodiscard]] material* get_material() const override;
        [[nodiscard]] glm::mat4 get_transform() const override;

    private:
        // pos in world coords
        float x_, y_;
        // dimensions in world coords
        float width_, height_;
        // movement speed in world units per second
        float speed_;

        mesh* mesh_ = nullptr;
        material* material_ = nullptr;
    };
}
