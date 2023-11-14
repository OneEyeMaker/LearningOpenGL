#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 globalUpDirection, glm::vec3 position) :
        globalUpDirection(globalUpDirection), position(position), frontDirection(), upDirection(), rightDirection() {
    yaw = -90.0f;
    pitch = 0.0f;
    aspectRatio = 1.0f;
    fieldOfView = 45.0f;
    movementSpeed = 1.0f;
    mouseSensitivity = 1.0f;
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + frontDirection, upDirection);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
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
    pitch = glm::clamp(pitch + rotation.y, -89.0f, 89.0f);
    updateVectors();
}

void Camera::processMouseScroll(float offset) {
    fieldOfView = glm::clamp(fieldOfView - offset, 1.0f, 90.0f);
}

void Camera::updateAspectRatio(int width, int height) {
    aspectRatio = (float) width / (float) height;
}

void Camera::reset() {
    yaw = -90.0f;
    pitch = 0.0f;
    fieldOfView = 45.0f;
    updateVectors();
}

void Camera::setMovementSpeed(float speed) {
    movementSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity) {
    mouseSensitivity = sensitivity;
}

void Camera::updateVectors() {
    float yawInRadians = glm::radians(yaw);
    float pitchInRadians = glm::radians(pitch);
    frontDirection = glm::normalize(glm::vec3(
            glm::cos(yawInRadians) * glm::cos(pitchInRadians),
            glm::sin(pitchInRadians),
            glm::sin(yawInRadians) * glm::cos(pitchInRadians)
    ));
    rightDirection = glm::normalize(glm::cross(frontDirection, globalUpDirection));
    upDirection = glm::normalize(glm::cross(rightDirection, frontDirection));
}
