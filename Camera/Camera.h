#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

enum camMove {
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_RIGHT,
    CAM_LEFT,
    CAM_UP
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    ~Camera();

    inline glm::mat4 getViewMatrix() { return glm::lookAt(Pos, Pos + Front, Up); }
    void processKeyInput(camMove, float);
    void processMouseMovement(float, float, bool);
    void processMouseScroll(float);

    glm::vec3 Pos;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float yaw;
    float pitch;
    float speed;
    float sens;
    float zoom;

    void updateCameraVectors();

    inline GLFWwindow* cameraGetWindow() const { return window; }
    inline void cameraCurrentWorkingWindow(GLFWwindow* win) { this->window = win; }
private:
    GLFWwindow* window;
};

#endif

