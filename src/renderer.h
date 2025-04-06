#pragma once
#include <vector>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "renderable.h"
#include "shader.h"

namespace pongo
{
    class renderer
    {
      public:
        renderer() = default;
        ~renderer() = default;

        void begin_scene();
        void submit(const renderable& r);
        void end_scene(shader& s);
        void clear();

      private:
        struct render_command
        {
            std::shared_ptr<mesh> mesh_ptr;
            std::shared_ptr<material> material_ptr;
            glm::mat4 transform;

            bool operator<(const render_command& other) const
            {
                // sort by material pointer for batching
                return material_ptr < other.material_ptr;
            }
        };

        std::vector<render_command> render_queue_;
    };
} // namespace pongo
