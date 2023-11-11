#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

    void setIcon() const;

    void setupCallbacks() const;

    bool setupRendering();

    void render();

    void dispose();

    static bool isSetupComplete;

    Mesh mesh;
    Shader shader;
    glm::vec3 meshRotation;
    glm::vec3 inputAxes;
    float aspectRatio;
    GLFWwindow *window;
};

#endif //LEARNINGOPENGL_APPLICATION_H
