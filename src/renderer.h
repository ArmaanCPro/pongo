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
        renderer();
        ~renderer();

        void begin_scene();
        void submit(const renderable& r);
        void end_scene(shader& s);
        void clear();

    private:
        struct render_command
        {
            std::shared_ptr<mesh> mesh;
            std::shared_ptr<material> material;
            glm::mat4 transform;

            bool operator<(const render_command& other) const
            {
                // sort by material pointer for batching
                return material < other.material;
            }
        };

        std::vector<render_command> render_queue_;
    };
}
