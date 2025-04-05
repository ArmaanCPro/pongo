#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "material.h"

namespace pongo
{
    class renderable
    {
    public:
        virtual ~renderable() = default;
        [[nodiscard]] virtual mesh* get_mesh() const = 0;
        [[nodiscard]] virtual material* get_material() const = 0;
        [[nodiscard]] virtual glm::mat4 get_transform() const = 0;
    };
}
