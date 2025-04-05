#include "paddle.h"

#include "settings.h"

namespace pongo
{
    paddle::paddle(float x, float y, float width, float height, float speed, const glm::vec4& color)
        :
        x_(x),
        y_(y),
        width_(width),
        height_(height),
        speed_(speed)
    {
        // create rectangle mesh vertices
        std::vector<float> vertices =
        {
            // positions         // texture coords
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,

            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        };

        mesh_ = new mesh(vertices);
        material_ = new material(color);
    }

    paddle::~paddle()
    {
        delete mesh_;
        delete material_;
    }

    void paddle::move_up(float delta_time)
    {
        y_ += speed_ * delta_time;
        if (y_ + height_ / 2 > WORLD_HEIGHT)
            y_ = WORLD_HEIGHT - height_ / 2;
    }

    void paddle::move_down(float delta_time)
    {
        y_ -= speed_ * delta_time;
        if (y_ - height_ / 2 < 0)
            y_ = height_ / 2;
    }

    mesh* paddle::get_mesh() const
    {
        return mesh_;
    }

    material* paddle::get_material() const
    {
        return material_;
    }

    glm::mat4 paddle::get_transform() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x_, y_, 0.0f));
        model = glm::scale(model, glm::vec3(width_, height_, 1.0f));
        return model;
    }
}
