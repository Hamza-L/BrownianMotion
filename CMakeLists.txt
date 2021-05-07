cmake_minimum_required(VERSION 3.17)
project(BirdFLock)

set(CMAKE_CXX_STANDARD 17)

IF (APPLE)
    #SET(GUI_TYPE MACOSX_BUNDLE shapes/vert.h)
    include_directories(/usr/local/include)
    include_directories(/Users/hamzalah/VulkanSDK/macOS/include)
    #include_directories(/usr/local/Cellar/glfw/HEAD-9477311/include)

    #add ${GUI_TYPE} after VulkanTesting (ie target) to compile into app
    add_executable(BirdFLock main.cpp shapes/vert.h shapes/Cube.h shapes/Triangle.h shapes/Plane.h shapes/Node.h newVulkanApp.cpp newVulkanApp.h vulkanWindow.cpp vulkanWindow.h vulkanPipeline.cpp vulkanPipeline.h vulkanDevice.cpp vulkanDevice.h vulkanSwapChain.cpp vulkanSwapChain.h vulkanModel.cpp vulkanModel.h shapes/Icosahedron.h stb_image.h stb_image.h)

    target_link_libraries(BirdFLock "/usr/local/lib/libglfw.3.4.dylib")
    target_link_libraries(BirdFLock "/Users/hamzalah/VulkanSDK/macOS/lib/libvulkan.1.2.162.dylib")
ENDIF(APPLE)
IF(WIN32)
    #include_directories(/usr/local/include)
    include_directories(C:/VulkanSDK/1.2.170.0/Include)
    include_directories(C:/Users/Hamza/CLionProjects/BirdFlock/lib/glfw-3.3.4.bin.WIN64/include)
    include_directories(C:/VulkanSDK/1.2.170.0/Third-Party/Include)

    #add ${GUI_TYPE} after VulkanTesting (ie target) to compile into app
    add_executable(BirdFLock main.cpp shapes/vert.h shapes/Cube.h shapes/Triangle.h shapes/Plane.h shapes/Node.h shapes/Icosahedron.h  stb_image.h vulkanWindow.cpp vulkanWindow.h newVulkanApp.cpp newVulkanApp.h vulkanPipeline.cpp vulkanPipeline.h vulkanDevice.cpp vulkanDevice.h vulkanSwapChain.cpp vulkanSwapChain.h vulkanModel.cpp vulkanModel.h stb_image.h)

    target_link_libraries(BirdFLock "C:/Users/Hamza/CLionProjects/BirdFlock/lib/glfw-3.3.4.bin.WIN64/lib-mingw-w64/libglfw3.a")
    target_link_libraries(BirdFLock "C:/VulkanSDK/1.2.170.0/Lib/vulkan-1.lib")
ENDIF(WIN32)

#for optimization
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


#target_link_libraries(VulkanTesting "/Users/hamzalah/VulkanSDK/macOS/lib/libvulkan.1.dylib")