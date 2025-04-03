#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <stdexcept>

namespace pongo
{
    class window
    {
    public:
        // Delete copy constructor and assignment operator
        window(const window&) = delete;
        window& operator=(const window&) = delete;

        // Get the singleton instance
        static window& get_instance();

        // Initialize the window (can only be called once)
        void initialize(int scr_width, int scr_height, const std::string& title);

        // Shutdown and cleanup
        void shutdown();

        // Window ops
        bool should_close() const;
        void set_should_close(bool should_close);
        int get_key_state(int keycode) const;
        void swap_and_poll();

        // Get the GLFW window pointer
        GLFWwindow* get_native_window() const { return window_; }

    private:
        // Private constructor / destructor
        window() = default;
        ~window();

        // Internal GLFW window pointer
        GLFWwindow* window_ = nullptr;
        bool initialized_ = false;
    };
}
