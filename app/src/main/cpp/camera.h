#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

class Camera {
public:
    Camera(float aspectRatio);
    
    void setPosition(float x, float y, float z);
    void getPosition(float* pos) const;
    void lookAt(float targetX, float targetY, float targetZ);
    void rotate(float pitch, float yaw);
    void update(float deltaTime);
    
    void getViewMatrix(float* matrix) const;
    void getProjectionMatrix(float* matrix) const;
    
private:
    void updateVectors();
    
    float position[3];
    float target[3];
    float up[3];
    float forward[3];
    float right[3];
    
    float pitch;
    float yaw;
    float roll;
    
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

#endif
