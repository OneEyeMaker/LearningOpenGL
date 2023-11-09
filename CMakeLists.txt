cmake_minimum_required(VERSION 3.26)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(
        _GLFW_WIN32
        STB_IMAGE_IMPLEMENTATION
)

include_directories(
        ../include
)

set(LIB_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib/${CMAKE_BUILD_TYPE})

link_libraries(
        opengl32.lib
        ${LIB_DIRECTORY}/glfw3.lib
)

add_executable(LearningOpenGL
        main.cpp
        glad.c
        Application.cpp
        Application.h
)

add_custom_target(CopyResources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_custom_target(CopyShaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
)
add_dependencies(LearningOpenGL
        CopyResources
        CopyShaders
)
