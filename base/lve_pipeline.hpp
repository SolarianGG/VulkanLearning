#pragma once

#include <string>
#include <vector>

#include "lve_engine_device.hpp"

namespace lve {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class LvePipeline {
    public:
        LvePipeline(LveDevice& device,
                    const std::string& vertShaderPath, 
                    const std::string& fragShaderPath,
                    const PipelineConfigInfo& configInfo);
        ~LvePipeline();

        LvePipeline(const LvePipeline& other) = delete;
        LvePipeline& operator=(const LvePipeline& other) = delete;
        LvePipeline(LvePipeline&& other) noexcept = delete;
        LvePipeline& operator=(LvePipeline&& other) noexcept = delete;

        void Bind(VkCommandBuffer commandBuffer);
        static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> ReadFile(const std::string& filePath);

        void CreateGraphicsPipeline(const std::string& vertShaderPath, 
                                    const std::string& fragShaderPath,
                                    const PipelineConfigInfo& configInfo);


        void CreateShaderModule(const std::vector<char>& code, VkShaderModule *shaderModule);

        LveDevice& device_;
        VkPipeline graphicsPipeline_;
        VkShaderModule vertShaderModule_;
        VkShaderModule fragShaderModule_;
    };
}