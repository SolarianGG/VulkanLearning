#pragma once

#include "base/lve_window.hpp"
#include "base/lve_pipeline.hpp"
#include "base/lve_engine_device.hpp"
#include "base/lve_engine_swap_chain.hpp"

#include <memory>
#include <vector>

namespace lve {

    class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp& other) = delete;
        FirstApp& operator=(const FirstApp& other) = delete;
        FirstApp(FirstApp&& other) noexcept = delete;
        FirstApp& operator=(FirstApp&& other) noexcept = delete;

        void Run();
    private:
        void CreatePipelinelayout();
        void CreatePipeline();
        void CreateCommandBuffers();
        void DrawFrame();

        LveWindow window_{WIDTH, HEIGHT, "Hello Vulkan!"};
        LveDevice device_{window_};
        LveSwapChain swapChain_{device_, window_.GetExtent()};
        std::unique_ptr<LvePipeline> pipeline_;
        VkPipelineLayout pipelineLayout_;
        std::vector<VkCommandBuffer> commandBuffers_;
    };
    

}