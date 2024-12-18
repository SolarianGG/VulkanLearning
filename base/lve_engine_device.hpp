#pragma once

#include "lve_window.hpp"

// std lib headers
#include <string>
#include <vector>

namespace lve {

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;
  bool IsComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

class LveDevice {
 public:
#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

  LveDevice(LveWindow &window);
  ~LveDevice();

  // Not copyable or movable
  LveDevice(const LveDevice &) = delete;
  void operator=(const LveDevice &) = delete;
  LveDevice(LveDevice &&) = delete;
  LveDevice &operator=(LveDevice &&) = delete;

  VkCommandPool GetCommandPool() { return commandPool; }
  VkDevice Device() { return device_; }
  VkSurfaceKHR Surface() { return surface_; }
  VkQueue GraphicsQueue() { return graphicsQueue_; }
  VkQueue PresentQueue() { return presentQueue_; }

  SwapChainSupportDetails getSwapChainSupport() { return QuerySwapChainSupport(physicalDevice); }
  uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  QueueFamilyIndices findPhysicalQueueFamilies() { return FindQueueFamilies(physicalDevice); }
  VkFormat FindSupportedFormat(
      const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

  // Buffer Helper Functions
  void CreateBuffer(
      VkDeviceSize size,
      VkBufferUsageFlags usage,
      VkMemoryPropertyFlags properties,
      VkBuffer &buffer,
      VkDeviceMemory &bufferMemory);
  VkCommandBuffer BeginSingleTimeCommands();
  void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
  void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void CopyBufferToImage(
      VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

  void CreateImageWithInfo(
      const VkImageCreateInfo &imageInfo,
      VkMemoryPropertyFlags properties,
      VkImage &image,
      VkDeviceMemory &imageMemory);

  VkPhysicalDeviceProperties properties;

 private:
  void CreateInstance();
  void SetupDebugMessenger();
  void CreateSurface();
  void PickPhysicalDevice();
  void CreateLogicalDevice();
  void CreateCommandPool();

  // helper functions
  bool IsDeviceSuitable(VkPhysicalDevice device);
  std::vector<const char *> GetRequiredExtensions();
  bool CheckValidationLayerSupport();
  QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
  void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  void HasGflwRequiredInstanceExtensions();
  bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  LveWindow &window;
  VkCommandPool commandPool;

  VkDevice device_;
  VkSurfaceKHR surface_;
  VkQueue graphicsQueue_;
  VkQueue presentQueue_;

  const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
  const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};

} 