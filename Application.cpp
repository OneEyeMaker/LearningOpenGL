#include <iostream>

#include "Application.h"

bool Application::initialize() {
    if (!glfwInit()) {
        std::cout << "Error: unable to initialize GLFW." << std::endl;
        return false;
    }
    glfwSetErrorCallback(handleLibraryError);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(640, 640, "Learning OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Error: unable to create window." << std::endl;
        dispose();
        return false;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Error: unable to detect OpenGL implementation." << std::endl;
        dispose();
        return false;
    }
    return true;
}

void Application::run() {
    setupCallbacks();
    setupRendering();
    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    dispose();
}

void Application::setupCallbacks() {
    glfwSetFramebufferSizeCallback(window, resizeWindowFramebuffer);
    glfwSetKeyCallback(window, handleKeyEvent);
}

void Application::setupRendering() {
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::dispose() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void Application::handleLibraryError(int code, const char *message) {
    std::cout << "GLFW error: [" << code << "] " << message << std::endl;
}

void Application::resizeWindowFramebuffer([[maybe_unused]] GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::handleKeyEvent(GLFWwindow *window, int key, [[maybe_unused]] int scanCode, int action,
                                 [[maybe_unused]] int modifiers) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
