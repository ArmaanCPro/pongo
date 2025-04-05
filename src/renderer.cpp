#include "renderer.h"

#include "settings.h"

#include <glm/common.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace utility
{
    glm::vec2 world_to_ndc(float wx, float wy)
    {
        return glm::vec2(2.0f * wx / pongo::WORLD_WIDTH - 1.0f, 1.0f - 2.0f * wy / pongo::WORLD_HEIGHT);
    }
}

namespace pongo
{
    renderer::renderer()
    {
    }

    renderer::~renderer()
    {}

    void renderer::begin_scene()
    {
        render_queue_.clear();
    }

    void renderer::submit(const renderable& r)
    {
        render_queue_.push_back({
            r.get_mesh(),
            r.get_material(),
            r.get_transform()
        });
    }

    void renderer::end_scene(shader& s)
    {
        // sort render commands to minimize state changes
        std::sort(render_queue_.begin(), render_queue_.end());

        // setup shader
        s.use();

        material* current_material = nullptr;

        for (const auto& cmd : render_queue_)
        {
            // only bind material if it changed from previous
            if (current_material != cmd.material)
            {
                cmd.material->bind(s);
                current_material = cmd.material;
            }

            // set model transform
            s.SetMat4("u_Model", cmd.transform);

            // bind and draw mesh
            cmd.mesh->bind();
            cmd.mesh->draw();
        }
    }

    void renderer::clear()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
} // namespace pongo
