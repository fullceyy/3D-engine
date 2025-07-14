#include "Camera.h"

Camera::~Camera() {
    //delete window;

}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sens(SENS), zoom(ZOOM) {
    Pos = position;
    WorldUp = up;
    yaw = yaw;
    pitch = pitch;
    updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sens(SENS), zoom(ZOOM)
{
    Pos = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    yaw = yaw;
    pitch = pitch;
    updateCameraVectors();
}

void Camera::processKeyInput(camMove direction, float deltaTime) {
    float velocity = speed * deltaTime;
    if (direction == CAM_FORWARD) {
        Pos += Front * velocity;
    } if (direction == CAM_BACKWARD) {
        Pos -= Front * velocity;
    } if (direction == CAM_LEFT) {
        Pos -= Right * velocity;
    } if (direction == CAM_RIGHT) {
        Pos += Right * velocity;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constraintPitch) {
    xOffset *= sens;
    yOffset *= sens;

    yaw += xOffset;
    pitch += yOffset;

    if (constraintPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
    zoom -= (float)yOffset;
    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 45.0f) zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}