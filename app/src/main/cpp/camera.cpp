#include "camera.h"
#include <cstring>

Camera::Camera(float aspectRatio)
    : pitch(0.0f)
    , yaw(0.0f)
    , roll(0.0f)
    , fov(45.0f)
    , aspectRatio(aspectRatio)
    , nearPlane(0.1f)
    , farPlane(100.0f) {
    
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 0.0f;
    
    target[0] = 0.0f;
    target[1] = 0.0f;
    target[2] = 0.0f;
    
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    
    updateVectors();
}

void Camera::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void Camera::getPosition(float* pos) const {
    pos[0] = position[0];
    pos[1] = position[1];
    pos[2] = position[2];
}

void Camera::lookAt(float targetX, float targetY, float targetZ) {
    target[0] = targetX;
    target[1] = targetY;
    target[2] = targetZ;
    
    forward[0] = target[0] - position[0];
    forward[1] = target[1] - position[1];
    forward[2] = target[2] - position[2];
    
    float length = sqrt(forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2]);
    if (length > 0.0001f) {
        forward[0] /= length;
        forward[1] /= length;
        forward[2] /= length;
    }
    
    updateVectors();
}

void Camera::rotate(float pitchDelta, float yawDelta) {
    pitch += pitchDelta;
    yaw += yawDelta;
    
    if (pitch > 1.5f) pitch = 1.5f;
    if (pitch < -1.5f) pitch = -1.5f;
    
    updateVectors();
}

void Camera::updateVectors() {
    right[0] = forward[1] * up[2] - forward[2] * up[1];
    right[1] = forward[2] * up[0] - forward[0] * up[2];
    right[2] = forward[0] * up[1] - forward[1] * up[0];
    
    float length = sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
    if (length > 0.0001f) {
        right[0] /= length;
        right[1] /= length;
        right[2] /= length;
    }
}

void Camera::update(float deltaTime) {
}

void Camera::getViewMatrix(float* matrix) const {
    float f[3] = {
        target[0] - position[0],
        target[1] - position[1],
        target[2] - position[2]
    };
    
    float length = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    if (length > 0.0001f) {
        f[0] /= length;
        f[1] /= length;
        f[2] /= length;
    }
    
    float s[3] = {
        f[1] * up[2] - f[2] * up[1],
        f[2] * up[0] - f[0] * up[2],
        f[0] * up[1] - f[1] * up[0]
    };
    
    length = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
    if (length > 0.0001f) {
        s[0] /= length;
        s[1] /= length;
        s[2] /= length;
    }
    
    float u[3] = {
        s[1] * f[2] - s[2] * f[1],
        s[2] * f[0] - s[0] * f[2],
        s[0] * f[1] - s[1] * f[0]
    };
    
    matrix[0] = s[0];
    matrix[1] = u[0];
    matrix[2] = -f[0];
    matrix[3] = 0.0f;
    
    matrix[4] = s[1];
    matrix[5] = u[1];
    matrix[6] = -f[1];
    matrix[7] = 0.0f;
    
    matrix[8] = s[2];
    matrix[9] = u[2];
    matrix[10] = -f[2];
    matrix[11] = 0.0f;
    
    matrix[12] = -(s[0] * position[0] + s[1] * position[1] + s[2] * position[2]);
    matrix[13] = -(u[0] * position[0] + u[1] * position[1] + u[2] * position[2]);
    matrix[14] = f[0] * position[0] + f[1] * position[1] + f[2] * position[2];
    matrix[15] = 1.0f;
}

void Camera::getProjectionMatrix(float* matrix) const {
    float tanHalfFov = tan(fov * 0.5f * 3.14159265359f / 180.0f);
    
    memset(matrix, 0, 16 * sizeof(float));
    
    matrix[0] = 1.0f / (aspectRatio * tanHalfFov);
    matrix[5] = 1.0f / tanHalfFov;
    matrix[10] = farPlane / (nearPlane - farPlane);
    matrix[11] = -1.0f;
    matrix[14] = -(farPlane * nearPlane) / (farPlane - nearPlane);
}
