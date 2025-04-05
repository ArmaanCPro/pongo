#include "material.h"

namespace pongo
{

    material::material(const glm::vec4& color)
        :
        color_(color)
    {}

    void material::set_color(const glm::vec4& color)
    {
        color_ = color;
    }

    void material::bind(shader& s) const
    {
        s.SetVec4("u_Color", color_);
    }
}
