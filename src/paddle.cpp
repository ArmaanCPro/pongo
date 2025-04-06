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

        mesh* mesh_obj = new mesh(vertices);
        material* mat_obj = new material(color);
        renderable_ = new renderable_component(mesh_obj, mat_obj, glm::mat4(1.0f));

        update_transform();
    }

    paddle::~paddle()
    {
        delete renderable_;
    }

    void paddle::move_up(float delta_time)
    {
        y_ += speed_ * delta_time;
        if (y_ + height_ / 2 > WORLD_HEIGHT)
            y_ = WORLD_HEIGHT - height_ / 2;

        update_transform();
    }

    void paddle::move_down(float delta_time)
    {
        y_ -= speed_ * delta_time;
        if (y_ - height_ / 2 < 0)
            y_ = height_ / 2;

        update_transform();
    }

    const renderable_component& paddle::get_renderable() const
    {
        return *renderable_;
    }

    void paddle::update_transform() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x_, y_, 0.0f));
        model = glm::scale(model, glm::vec3(width_, height_, 1.0f));
        renderable_->set_transform(model);
    }
}
