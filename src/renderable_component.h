#pragma once

#include "renderable.h"

namespace pongo
{
    class renderable_component : public renderable
    {
    public:
        renderable_component(mesh* mesh, material* material, const glm::mat4& transform)
            :
            mesh_(mesh), material_(material), transform_(transform)
        {}

        ~renderable_component() override
        {
            delete mesh_;
            delete material_;
        }

        // renderable interface
        [[nodiscard]] mesh* get_mesh() const override { return mesh_; }
        [[nodiscard]] material* get_material() const override { return material_; }
        [[nodiscard]] glm::mat4 get_transform() const override { return transform_; }

        void set_transform(const glm::mat4& transform) { transform_ = transform; }

    private:
        mesh* mesh_ = nullptr;
        material* material_ = nullptr;
        glm::mat4 transform_ = glm::mat4(1.0f);
    };
}
