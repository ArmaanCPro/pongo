#include "ball.h"
#include "paddle.h"
#include <cmath>

namespace pongo
{
    ball::ball(float x, float y, float vx, float vy, float radius)
        : x_(x), y_(y), vx_(vx), vy_(vy), radius_(radius) {}
    
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
}
