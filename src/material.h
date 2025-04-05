#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>
#include "shader.h"

namespace pongo
{
    class material
    {
    public:
        explicit material(const glm::vec4& color = glm::vec4(1.0f) );

        void set_color(const glm::vec4& color);
        void bind(shader& s) const;

    private:
        glm::vec4 color_;
    };
}
