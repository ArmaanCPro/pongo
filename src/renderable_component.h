#pragma once

#include "renderable.h"
#include <memory>

namespace pongo
{
    class renderable_component : public renderable
    {
    public:
        renderable_component(std::shared_ptr<mesh> mesh, std::shared_ptr<material> material, const glm::mat4& transform)
            :
            mesh_(std::move(mesh)), material_(std::move(material)), transform_(transform)
        {}

        // renderable interface
        [[nodiscard]] const std::shared_ptr<mesh>& get_mesh() const override { return mesh_; }
        [[nodiscard]] const std::shared_ptr<material>& get_material() const override { return material_; }
        [[nodiscard]] glm::mat4 get_transform() const override { return transform_; }

        void set_transform(const glm::mat4& transform) { transform_ = transform; }

    private:
        std::shared_ptr<mesh> mesh_ = nullptr;
        std::shared_ptr<material> material_ = nullptr;
        glm::mat4 transform_ = glm::mat4(1.0f);
    };
}
