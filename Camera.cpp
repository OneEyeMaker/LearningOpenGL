#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 globalUpDirection, glm::vec3 position) :
        globalUpDirection(globalUpDirection), position(position), frontDirection(), upDirection(), rightDirection() {
    yaw = -glm::pi<float>() * 0.5f;
    pitch = 0.0f;
    aspectRatio = 1.0f;
    fieldOfView = glm::pi<float>() * 0.25f;
    movementSpeed = 1.0f;
    mouseSensitivity = 1.0f;
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + frontDirection, upDirection);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(fieldOfView, aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboardInput(const glm::vec3 &axes, float deltaTime) {
    const glm::vec3 movement = axes * movementSpeed * deltaTime;
    position += movement.x * rightDirection;
    position += movement.y * upDirection;
    position += movement.z * frontDirection;
}

void Camera::processMouseInput(const glm::vec2 &offset) {
    const glm::vec2 rotation = offset * mouseSensitivity;
    yaw += rotation.x;
    pitch = glm::clamp(pitch + rotation.y, -glm::pi<float>() * 0.49f, glm::pi<float>() * 0.49f);
    updateVectors();
}

void Camera::processMouseScroll(float offset) {
    fieldOfView = glm::clamp(fieldOfView - offset, glm::pi<float>() / 64.0f, glm::pi<float>() * 0.5f);
}

void Camera::updateAspectRatio(int width, int height) {
    aspectRatio = (float) width / (float) height;
}

void Camera::setMovementSpeed(float speed) {
    movementSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity) {
    mouseSensitivity = sensitivity;
}

void Camera::updateVectors() {
    frontDirection = glm::normalize(glm::vec3(
            glm::cos(yaw) * glm::cos(pitch),
            glm::sin(pitch),
            glm::sin(yaw) * glm::cos(pitch)
    ));
    rightDirection = glm::normalize(glm::cross(frontDirection, globalUpDirection));
    upDirection = glm::normalize(glm::cross(rightDirection, frontDirection));
}
