#include "paddle.h"

#include "settings.h"

namespace pongo
{
    paddle::paddle(float x, float y, float width, float height, float speed)
        :
        x_(x),
        y_(y),
        width_(width),
        height_(height),
        speed_(speed)
    {}

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
}
