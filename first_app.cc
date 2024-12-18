#include "first_app.hpp"

#include <array>
#include <stdexcept>

namespace lve {

    FirstApp::FirstApp()
    {
        CreatePipelinelayout();
        CreatePipeline();
        CreateCommandBuffers();
    }

    FirstApp::~FirstApp()
    {
        vkDestroyPipelineLayout(device_.Device(), pipelineLayout_, nullptr);
    }

    void FirstApp::Run()
    {
        while (!window_.ShouldClose())
        {
            glfwPollEvents();
            DrawFrame();
        }

        vkDeviceWaitIdle(device_.Device());
    }

    void FirstApp::CreatePipelinelayout()
    {
        VkPipelineLayoutCreateInfo layoutInfo{};

        layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layoutInfo.setLayoutCount = 0;
        layoutInfo.pSetLayouts = nullptr;
        layoutInfo.pushConstantRangeCount = 0;
        layoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(device_.Device(), &layoutInfo, nullptr, &pipelineLayout_) !=
         VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void FirstApp::CreatePipeline()
    {
        auto pipelineConfig = 
           LvePipeline::DefaultPipelineConfigInfo(swapChain_.Width(), swapChain_.Height());
        
        pipelineConfig.renderPass = swapChain_.GetRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout_;

        pipeline_ = 
           std::make_unique<LvePipeline>
           (device_, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
    }

    void FirstApp::CreateCommandBuffers()
    {
        commandBuffers_.resize(swapChain_.ImageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device_.GetCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers_.size());

        if (vkAllocateCommandBuffers(device_.Device(), &allocInfo, commandBuffers_.data())
            != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffers");
        }

        for (int i = 0; i != commandBuffers_.size(); ++i)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers_.at(i), &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to begin command buffer");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = swapChain_.GetRenderPass();
            renderPassInfo.framebuffer = swapChain_.GetFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChain_.GetSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};

            clearValues[0].color = {.1f, .1f, .1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers_.at(i), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            pipeline_->Bind(commandBuffers_.at(i));
            vkCmdDraw(commandBuffers_.at(i), 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers_.at(i));

            if(vkEndCommandBuffer(commandBuffers_.at(i)) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to record command buffer");
            }
        }
    }

    void FirstApp::DrawFrame()
    {
        uint32_t imageIndex;
        auto result = swapChain_.AcquireNextImage(&imageIndex);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Failed to acquire swap chaine image");
        }

        result = swapChain_.SubmitCommandBuffers(&commandBuffers_.at(imageIndex), &imageIndex);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present swap chain image");
        }
    }
}