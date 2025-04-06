#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "material.h"

#include <memory>

namespace pongo
{
    class renderable
    {
    public:
        virtual ~renderable() = default;
        [[nodiscard]] virtual const std::shared_ptr<mesh>& get_mesh() const = 0;
        [[nodiscard]] virtual const std::shared_ptr<material>& get_material() const = 0;
        [[nodiscard]] virtual glm::mat4 get_transform() const = 0;
    };
}
