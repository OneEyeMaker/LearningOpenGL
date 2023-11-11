#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include "Application.h"

bool Application::isSetupComplete = false;

bool Application::setup() {
    if (!glfwInit()) {
        std::cout << "Error: unable to initialize GLFW." << std::endl;
        return false;
    }
    isSetupComplete = true;
    return true;
}

void Application::finalize() {
    glfwTerminate();
}

Application::Application() : meshRotation(0.0f, 0.0f, 0.0f) {
    aspectRatio = 1.0f;
    window = nullptr;
}

bool Application::initialize() {
    if (!isSetupComplete) {
        std::cout << "Error: application setup is not completed." << std::endl;
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
    glfwSetWindowUserPointer(window, this);
    setIcon();
    return true;
}

void Application::run() {
    setupCallbacks();
    if (setupRendering()) {
        while (!glfwWindowShouldClose(window)) {
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    dispose();
}

void Application::setIcon() const {
    std::string iconPaths[] = {
            "resources/icons/icon128.png",
            "resources/icons/icon64.png",
            "resources/icons/icon32.png"
    };
    GLFWimage icons[3];
    int count = 0;
    for (const auto &iconPath: iconPaths) {
        int width;
        int height;
        int channelsCount;
        unsigned char *imageData = stbi_load(iconPath.c_str(), &width, &height, &channelsCount, 0);
        if (imageData != nullptr) {
            icons[count++] = GLFWimage(width, height, imageData);
        }
    }
    if (count > 0) {
        glfwSetWindowIcon(window, count, icons);
    }
    while (count > 0) {
        stbi_image_free(icons[--count].pixels);
    }
}

void Application::setupCallbacks() const {
    glfwSetFramebufferSizeCallback(window, resizeWindowFramebuffer);
    glfwSetKeyCallback(window, handleKeyEvent);
}

bool Application::setupRendering() {
    if (!shader.compileAndLink("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        return false;
    }
    if (!mesh.loadCube()) {
        return false;
    }
    shader.use();
    mesh.setupRendering(shader);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    return true;
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    auto model = glm::toMat4(glm::quat(meshRotation));
    auto view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
    auto projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    shader.setMatrix4("modelTransform", model);
    shader.setMatrix4("viewTransform", view);
    shader.setMatrix4("projectionTransform", projection);
    mesh.draw();
}

void Application::dispose() {
    if (window != nullptr) {
        mesh.dispose();
        shader.dispose();
        glfwSetWindowUserPointer(window, nullptr);
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

void Application::handleLibraryError(int code, const char *message) {
    std::cout << "GLFW error: [" << code << "] " << message << std::endl;
}

void Application::resizeWindowFramebuffer([[maybe_unused]] GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto *application = (Application *) glfwGetWindowUserPointer(window);
    if (application != nullptr) {
        application->aspectRatio = (float) width / (float) height;
    }
}

void Application::handleKeyEvent(GLFWwindow *window, int key, [[maybe_unused]] int scanCode, int action,
                                 [[maybe_unused]] int modifiers) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
