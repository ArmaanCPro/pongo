#include "ball.h"
#include "paddle.h"
#include <cmath>

namespace pongo
{
    ball::ball(float x, float y, float vx, float vy, float radius, const glm::vec4& color)
        : x_(x), y_(y), vx_(vx), vy_(vy), radius_(radius)
    {
        // Create a simple circle mesh for the ball (actually a hexagon)
        std::vector<float> vertices;
        const int segments = 12;

        // Center vertex
        vertices.push_back(0.0f);  // x
        vertices.push_back(0.0f);  // y
        vertices.push_back(0.0f);  // z
        vertices.push_back(0.5f);  // tex u
        vertices.push_back(0.5f);  // tex v

        // Create triangles
        for (int i = 0; i <= segments; i++) {
            const float angle = 2.0f * M_PI * float(i) / float(segments);
            const float angle_x = std::cos(angle);
            const float angle_y = std::sin(angle);

            vertices.push_back(angle_x);       // x
            vertices.push_back(angle_y);       // y
            vertices.push_back(0.0f);        // z
            vertices.push_back(angle_x * 0.5f + 0.5f);  // tex u
            vertices.push_back(angle_y * 0.5f + 0.5f);  // tex v

            // We create a triangle fan, so we need to repeat the center and the first vertex
            if (i < segments) {
                vertices.push_back(0.0f);  // center x
                vertices.push_back(0.0f);  // center y
                vertices.push_back(0.0f);  // center z
                vertices.push_back(0.5f);  // center tex u
                vertices.push_back(0.5f);  // center tex v
            }
        }

        mesh_ = new mesh(vertices);
        material_ = new material(color);
    }
    
    void ball::move(float delta_time)
    {
        x_ += vx_ * delta_time;
        y_ += vy_ * delta_time;
    }
    
    void ball::bounce_x()
    {
        vx_ *= -1.0f;
    }
    
    void ball::bounce_y()
    {
        vy_ *= -1.0f;
    }
    
    void ball::reset(float x, float y, float vx, float vy)
    {
        x_ = x;
        y_ = y;
        vx_ = vx;
        vy_ = vy;
    }
    
    void ball::accelerate(float factor)
    {
        vx_ *= factor;
        vy_ *= factor;
    }
    
    bool ball::collides_with_paddle(const paddle& p) const
    {
        // Simplified AABB <-> Circle collision detection
        // Find the closest point on the paddle to the ball
        float closest_x = std::max(p.getX() - p.getWidth()/2, std::min(x_, p.getX() + p.getWidth()/2));
        float closest_y = std::max(p.getY() - p.getHeight()/2, std::min(y_, p.getY() + p.getHeight()/2));
        
        // Calculate distance between the closest point and ball center
        float distance_x = x_ - closest_x;
        float distance_y = y_ - closest_y;
        float distance_squared = distance_x * distance_x + distance_y * distance_y;
        
        // If the distance is less than the ball's radius, collision occurred
        return distance_squared < (radius_ * radius_);
    }
    
    bool ball::is_out_of_bounds_x(float min_x, float max_x) const
    {
        return (x_ - radius_ < min_x) || (x_ + radius_ > max_x);
    }
    
    bool ball::is_out_of_bounds_y(float min_y, float max_y) const
    {
        return (y_ - radius_ < min_y) || (y_ + radius_ > max_y);
    }

    mesh* ball::get_mesh() const
    {
        return mesh_;
    }

    material* ball::get_material() const
    {
        return material_;
    }

    glm::mat4 ball::get_transform() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x_, y_, 0.0f));
        model = glm::scale(model, glm::vec3(radius_, radius_, 1.0f));
        return model;
    }
}
