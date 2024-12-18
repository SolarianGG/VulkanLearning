#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace lve {
    class LveWindow {

        void InitWindow();

        const int width_;
        const int height_;

        std::string windowName_;
        GLFWwindow *window_;

        public:
            LveWindow(int width, int height, const std::string& name);

            LveWindow(const LveWindow& other) = delete;
            LveWindow& operator=(const LveWindow& other) = delete;
            LveWindow(LveWindow&& other) = delete;
            LveWindow& operator=(LveWindow&& other) = delete;


            bool ShouldClose() const { return glfwWindowShouldClose(window_); }
            VkExtent2D GetExtent() const { return {static_cast<uint32_t>(width_), static_cast<uint32_t>(height_)}; }
            void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
            ~LveWindow();
    };
}