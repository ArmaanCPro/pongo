#include "ball.h"
#include "paddle.h"
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>  // For additional vector operations

namespace pongo
{
    ball::ball(float x, float y, float vx, float vy, float radius, const glm::vec4& color)
        : x_(x), y_(y), vx_(vx), vy_(vy), radius_(radius)
    {
        // circle mesh for a ball
        std::vector<float> vertices;
        const int segments = 18;

        // Center vertex (first vertex in a triangle fan)
        vertices.push_back(0.0f);  // x
        vertices.push_back(0.0f);  // y
        vertices.push_back(0.0f);  // z
        vertices.push_back(0.5f);  // tex u
        vertices.push_back(0.5f);  // tex v

        // Add vertices around the perimeter
        for (int i = 0; i <= segments; i++) {
            const float angle = 2.0f * M_PI * float(i) / float(segments);
            const float angle_x = std::cos(angle);
            const float angle_y = std::sin(angle);

            vertices.push_back(angle_x);       // x
            vertices.push_back(angle_y);       // y
            vertices.push_back(0.0f);          // z
            vertices.push_back(angle_x * 0.5f + 0.5f);  // tex u
            vertices.push_back(angle_y * 0.5f + 0.5f);  // tex v
        }

        mesh_ = new mesh(vertices, GL_TRIANGLE_FAN);
        material_ = new material(color);
    }

    ball::~ball()
    {
        delete mesh_;
        delete material_;
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

    void ball::handle_paddle_collision(const paddle& p)
    {
        if (!collides_with_paddle(p))
        {
            return;
        }

        // Find the closest point on the paddle to the ball
        float paddle_left = p.getX() - p.getWidth() / 2;
        float paddle_right = p.getX() + p.getWidth() / 2;
        float paddle_top = p.getY() + p.getHeight() / 2;
        float paddle_bottom = p.getY() - p.getHeight() / 2;

        float closest_x = glm::clamp(x_, paddle_left, paddle_right);
        float closest_y = glm::clamp(y_, paddle_bottom, paddle_top);

        // Ball position and closest point on paddle as vectors
        glm::vec2 ball_pos(x_, y_);
        glm::vec2 closest_point(closest_x, closest_y);

        // Vector from closest point to ball center (surface normal)
        glm::vec2 normal = ball_pos - closest_point;

        // Handle edge case: if ball is inside paddle
        if (glm::length(normal) < 0.0001f)
        {
            // Find the nearest edge to determine the normal
            float dist_left = std::abs(x_ - paddle_left);
            float dist_right = std::abs(x_ - paddle_right);
            float dist_top = std::abs(y_ - paddle_top);
            float dist_bottom = std::abs(y_ - paddle_bottom);

            float min_dist = glm::min(glm::min(dist_left, dist_right),
                                      glm::min(dist_top, dist_bottom));

            if (min_dist == dist_left)
                normal = glm::vec2(-1, 0);
            else if (min_dist == dist_right)
                normal = glm::vec2(1, 0);
            else if (min_dist == dist_top)
                normal = glm::vec2(0, 1);
            else
                normal = glm::vec2(0, -1);
        }

        // Normalize the normal vector
        normal = glm::normalize(normal);

        // Apply position correction to move the ball outside the paddle
        float length = glm::distance(ball_pos, closest_point);
        float overlap = radius_ - length;

        if (length < radius_)
        {
            // Move ball out of paddle with a small extra buffer
            ball_pos += normal * overlap * 1.01f;
            x_ = ball_pos.x;
            y_ = ball_pos.y;
        }

        // ------------ REFLECTION USING DOT PRODUCT ------------

        // Current velocity as a vector
        glm::vec2 velocity(vx_, vy_);

        // Calculate the dot product between the velocity and the normal
        float dot_product = glm::dot(velocity, normal);

        // Reflection formula: v' = v - 2(v·n)n
        glm::vec2 reflection = velocity - 2.0f * dot_product * normal;

        // ------------ OPTIONAL GAMEPLAY ENHANCEMENTS ------------

        // Add some variation based on where the ball hit the paddle
        glm::vec2 paddle_center(p.getX(), p.getY());
        glm::vec2 paddle_size(p.getWidth(), p.getHeight());
        glm::vec2 normalized_hit_pos = 2.0f * (ball_pos - paddle_center) / paddle_size;

        // Determine if hit was more on the side or top/bottom and add "english"
        if (glm::abs(normal.x) > glm::abs(normal.y))
        {
            // Side hit - adjust based on vertical position
            reflection.y += normalized_hit_pos.y * 15.0f; // Vertical "english"
        }
        else
        {
            // Top/bottom hit - adjust based on horizontal position
            reflection.x += normalized_hit_pos.x * 15.0f; // Horizontal "english"
        }

        // Optional: slightly increase ball speed with each hit
        float current_speed = glm::length(reflection);
        float speed_increase = 1.02f; // 2% increase

        // Normalize and scale to new speed
        float new_speed = current_speed * speed_increase;
        reflection = glm::normalize(reflection) * new_speed;

        // Optional: Cap maximum speed
        float max_speed = 150.0f; // Adjust as needed
        current_speed = glm::length(reflection);

        if (current_speed > max_speed)
        {
            reflection = glm::normalize(reflection) * max_speed;
        }

        // Update the ball's velocity
        vx_ = reflection.x;
        vy_ = reflection.y;
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
