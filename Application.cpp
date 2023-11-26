#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
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

Application::Application() :
        camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f)),
        cameraInputAxes(0.0f), inputAxes(0.0f), lastMousePosition(-1.0f), mouseOffset(0.0f) {
    selectedMesh = 0;
    lastFrameTime = 0.0f;
    deltaTime = 0.0f;
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
    glfwSetCursorPosCallback(window, handleMouseEvent);
    glfwSetScrollCallback(window, handleMouseScrollEvent);
}

bool Application::setupRendering() {
    if (!shader.compileAndLink("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        return false;
    }
    if (!cube.createCube()) {
        return false;
    }
    octahedron.useTexturesOf(cube);
    if (!octahedron.createOctahedron()) {
        return false;
    }
    for (int x = -1; x <= 1; x += 2) {
        for (int y = -1; y <= 1; y += 2) {
            for (int z = -1; z <= 1; z += 2) {
                meshPositions.emplace_back(x, y, z);
                meshRotations.emplace_back(0.0f);
            }
        }
    }
    camera.setMovementSpeed(2.0f);
    camera.setMouseSensitivity(0.0625f);
    shader.use();
    cube.attachTextures(shader);
    octahedron.attachTextures(shader);
    shader.setFloat("material.specularExponent", 16.0f);
    shader.setVector3("light.ambientColor", glm::vec3(0.25f, 0.25f, 0.25f));
    shader.setVector3("light.diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVector3("light.specularColor", glm::vec3(0.75f, 0.75f, 0.75f));
    shader.setVector3("light.attenuationCoefficient", glm::vec3(1.0f, 0.25f, 0.375f));
    shader.setFloat("light.innerCutOff", glm::cos(glm::radians(15.0f)));
    shader.setFloat("light.outerCutOff", glm::cos(glm::radians(25.0f)));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    lastFrameTime = (float) glfwGetTime();
    return true;
}

void Application::render() {
    auto currentFrameTime = (float) glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    meshRotations[selectedMesh] += inputAxes * (2.0f * deltaTime);
    camera.processKeyboardInput(cameraInputAxes, deltaTime);
    shader.setMatrix4("transform.view", camera.getViewMatrix());
    shader.setMatrix4("transform.projection", camera.getProjectionMatrix());
    shader.setVector3("light.position", camera.position + camera.frontDirection * 0.5f);
    shader.setVector3("light.direction", camera.frontDirection);
    shader.setVector3("viewPosition", camera.position);
    for (int index = 0; index < meshRotations.size(); ++index) {
        auto model = glm::translate(glm::mat4(1.0f), meshPositions[index]);
        model *= glm::toMat4(glm::quat(meshRotations[index]));
        auto normal = glm::inverseTranspose(glm::mat3(model));
        shader.setMatrix4("transform.model", model);
        shader.setMatrix3("transform.normal", normal);
        cube.drawElements();
    }
    auto model = glm::mat4(1.0f);
    auto normal = glm::inverseTranspose(glm::mat3(model));
    shader.setMatrix4("transform.model", model);
    shader.setMatrix3("transform.normal", normal);
    octahedron.drawArrays();
}

void Application::dispose() {
    if (window != nullptr) {
        cube.dispose();
        octahedron.dispose();
        shader.dispose();
        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
        application->camera.updateAspectRatio(width, height);
    }
}

void Application::handleKeyEvent(GLFWwindow *window, int key, [[maybe_unused]] int scanCode, int action,
                                 [[maybe_unused]] int modifiers) {
    if (key == GLFW_KEY_UNKNOWN) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    auto *application = (Application *) glfwGetWindowUserPointer(window);
    if (application == nullptr) {
        return;
    }
    if (action == GLFW_PRESS) {
        unsigned int size = application->meshPositions.size();
        switch (key) {
            case GLFW_KEY_W:
                application->cameraInputAxes.z = 1.0f;
                break;
            case GLFW_KEY_S:
                application->cameraInputAxes.z = -1.0f;
                break;
            case GLFW_KEY_A:
                application->cameraInputAxes.x = -1.0f;
                break;
            case GLFW_KEY_D:
                application->cameraInputAxes.x = 1.0f;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                application->cameraInputAxes.y = -1.0f;
                break;
            case GLFW_KEY_SPACE:
                application->cameraInputAxes.y = 1.0f;
                break;
            case GLFW_KEY_KP_5:
                application->meshRotations[application->selectedMesh] = glm::vec3(0.0f);
                break;
            case GLFW_KEY_KP_8:
                application->inputAxes.x = -1.0f;
                break;
            case GLFW_KEY_KP_2:
                application->inputAxes.x = 1.0f;
                break;
            case GLFW_KEY_KP_4:
                application->inputAxes.y = -1.0f;
                break;
            case GLFW_KEY_KP_6:
                application->inputAxes.y = 1.0f;
                break;
            case GLFW_KEY_KP_9:
                application->inputAxes.z = -1.0f;
                break;
            case GLFW_KEY_KP_7:
                application->inputAxes.z = 1.0f;
                break;
            case GLFW_KEY_KP_1:
                application->selectedMesh = (application->selectedMesh + size - 1) % size;
                break;
            case GLFW_KEY_KP_3:
                application->selectedMesh = (application->selectedMesh + 1) % size;
                break;
            case GLFW_KEY_KP_0:
                application->camera.reset();
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_W:
            case GLFW_KEY_S:
                application->cameraInputAxes.z = 0.0f;
                break;
            case GLFW_KEY_A:
            case GLFW_KEY_D:
                application->cameraInputAxes.x = 0.0f;
                break;
            case GLFW_KEY_LEFT_SHIFT:
            case GLFW_KEY_SPACE:
                application->cameraInputAxes.y = 0.0f;
                break;
            case GLFW_KEY_KP_2:
            case GLFW_KEY_KP_8:
                application->inputAxes.x = 0.0f;
                break;
            case GLFW_KEY_KP_4:
            case GLFW_KEY_KP_6:
                application->inputAxes.y = 0.0f;
                break;
            case GLFW_KEY_KP_7:
            case GLFW_KEY_KP_9:
                application->inputAxes.z = 0.0f;
                break;
            default:
                break;
        }
    }
}

void Application::handleMouseEvent(GLFWwindow *window, double xPosition, double yPosition) {
    auto *application = (Application *) glfwGetWindowUserPointer(window);
    if (application == nullptr) {
        return;
    }
    if (application->lastMousePosition.x < 0.0f && application->lastMousePosition.y < 0.0f) {
        application->lastMousePosition = glm::vec2(xPosition, yPosition);
    }
    application->mouseOffset = glm::vec2(xPosition - application->lastMousePosition.x,
                                         application->lastMousePosition.y - yPosition);
    application->lastMousePosition = glm::vec2(xPosition, yPosition);
    application->camera.processMouseInput(application->mouseOffset);
}

void Application::handleMouseScrollEvent(GLFWwindow *window, [[maybe_unused]] double xOffset, double yOffset) {
    auto *application = (Application *) glfwGetWindowUserPointer(window);
    if (application != nullptr) {
        application->camera.processMouseScroll((float) yOffset);
    }
}
