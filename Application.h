#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
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

    void setupRendering();

    void render();

    void dispose();

    GLFWwindow *window;
};

#endif //LEARNINGOPENGL_APPLICATION_H
