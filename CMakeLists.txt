cmake_minimum_required(VERSION 3.16)

project(VulkanLearning CXX)

if(WIN32)
include("C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()


find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_library(libbase 
    ${PROJECT_SOURCE_DIR}/base/lve_window.cc
    ${PROJECT_SOURCE_DIR}/base/lve_pipeline.cc
    ${PROJECT_SOURCE_DIR}/base/lve_engine_device.cc
    ${PROJECT_SOURCE_DIR}/base/lve_engine_device.cc
    ${PROJECT_SOURCE_DIR}/base/lve_engine_swap_chain.cc
)

target_link_libraries(libbase glfw Vulkan::Vulkan)

target_include_directories(libbase PUBLIC ${PROJECT_SOURCE_DIR}/base/)

add_executable(VulkanTest main.cc first_app.cc)

target_include_directories(libbase PUBLIC ${PROJECT_SOURCE_DIR}/)

target_link_libraries(VulkanTest libbase)


if(LINUX)
    add_custom_command(
        TARGET VulkanTest PRE_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/shader_compile.sh
    )
endif()

if(WIN32)
    add_custom_command(
        TARGET VulkanTest PRE_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}\\shader_compile.bat
    )
endif()
