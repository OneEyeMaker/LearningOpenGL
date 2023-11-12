#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

class Application {
public:
    static bool setup();

    static void finalize();

    Application();

    bool initialize();

    void run();

private:
    static void handleLibraryError(int code, const char *message);

    static void resizeWindowFramebuffer([[maybe_unused]] GLFWwindow *window, int width, int height);

    static void handleKeyEvent(GLFWwindow *window, int key, [[maybe_unused]] int scanCode, int action,
                               [[maybe_unused]] int modifiers);

    static void handleMouseEvent(GLFWwindow *window, double xPosition, double yPosition);

    void setIcon() const;

    void setupCallbacks() const;

    bool setupRendering();

    void render();

    void dispose();

    static bool isSetupComplete;

    Camera camera;
    Mesh mesh;
    Shader shader;
    std::vector<glm::vec3> meshPositions;
    std::vector<glm::vec3> meshRotations;
    glm::vec3 cameraInputAxes;
    glm::vec3 inputAxes;
    glm::vec2 lastMousePosition;
    glm::vec2 mouseOffset;
    unsigned int selectedMesh;
    float lastFrameTime;
    float deltaTime;
    float aspectRatio;
    GLFWwindow *window;
};

#endif //LEARNINGOPENGL_APPLICATION_H
