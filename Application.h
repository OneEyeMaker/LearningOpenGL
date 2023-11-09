#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    bool initialize();

    void run();

private:
    static void handleLibraryError(int code, const char *message);

    static void resizeWindowFramebuffer([[maybe_unused]] GLFWwindow *window, int width, int height);

    static void handleKeyEvent(GLFWwindow *window, int key, [[maybe_unused]] int scanCode, int action,
                               [[maybe_unused]] int modifiers);

    void setIcon();

    void setupCallbacks();

    void setupRendering();

    void render();

    void dispose();

    GLFWwindow *window = nullptr;
};

#endif //LEARNINGOPENGL_APPLICATION_H
