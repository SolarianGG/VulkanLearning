#include "lve_window.hpp"

#include <cassert>
#include <stdexcept>

namespace lve {
    LveWindow::LveWindow(int width, int height, const std::string& name)
       : width_(width), height_(height), windowName_(name)
    {
        InitWindow();
    }

    LveWindow::~LveWindow()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    void LveWindow::InitWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window_ = glfwCreateWindow
        (width_, height_, windowName_.c_str(),
        nullptr, nullptr);

        assert(window_);
    }

    void LveWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window_, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface");
        }
    }
}