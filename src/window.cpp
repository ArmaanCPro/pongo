#include "window.h"
#include <iostream>

namespace pongo
{
    window& window::get_instance()
    {
        static window instance;
        return instance;
    }

    void window::initialize(int scr_width, int scr_height, const std::string& title)
    {
        if (initialized_)
        {
            throw std::runtime_error("Window already initialized");
        }

        // initialization
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef PL_MACOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        window_ = glfwCreateWindow(scr_width, scr_height, title.c_str(), nullptr, nullptr);
        if (window_ == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window_);
        glfwSetFramebufferSizeCallback(window_,
            [](GLFWwindow*, int width, int height) {
                glViewport(0, 0, width, height);
            }
        );

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, scr_width, scr_height);
        initialized_ = true;
    }

    window::~window()
    {
        shutdown();
    }

    void window::shutdown()
    {
        if (window_)
        {
            glfwDestroyWindow(window_);
            glfwTerminate();
            window_ = nullptr;
            initialized_ = false;
        }
    }

    bool window::should_close() const
    {
        if (!window_) return true;
        return glfwWindowShouldClose(window_);
    }

    void window::set_should_close(bool should_close)
    {
        if (window_)
        {
            glfwSetWindowShouldClose(window_, should_close);
        }
    }

    int window::get_key_state(int keycode) const
    {
        if (!window_)
            return GLFW_RELEASE;
        return glfwGetKey(window_, keycode);
    }

    void window::swap_and_poll()
    {
        if (window_)
        {
            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
    }
}
