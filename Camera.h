#ifndef LEARNINGOPENGL_CAMERA_H
#define LEARNINGOPENGL_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 globalUpDirection, glm::vec3 position);

    [[nodiscard]] glm::mat4 getViewMatrix() const;

    [[nodiscard]] glm::mat4 getProjectionMatrix() const;

    void processKeyboardInput(const glm::vec3 &axes, float deltaTime);

    void processMouseInput(const glm::vec2 &offset);

    void processMouseScroll(float offset);

    void updateAspectRatio(int width, int height);

    void reset();

    void setMovementSpeed(float speed);

    void setMouseSensitivity(float sensitivity);

    const glm::vec3 globalUpDirection;

    glm::vec3 position;
    glm::vec3 frontDirection;
private:
    void updateVectors();

    glm::vec3 rightDirection;
    glm::vec3 upDirection;
    float yaw;
    float pitch;
    float aspectRatio;
    float fieldOfView;
    float movementSpeed;
    float mouseSensitivity;
};

#endif //LEARNINGOPENGL_CAMERA_H
