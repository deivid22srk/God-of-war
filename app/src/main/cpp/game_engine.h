#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <android_native_app_glue.h>
#include "vulkan_renderer.h"
#include "camera.h"
#include "player.h"

class GameEngine {
public:
    GameEngine(struct android_app* app);
    ~GameEngine();
    
    bool initialize();
    void update();
    void render();
    void handleTouch(int32_t action, float x, float y);
    
private:
    void updateUniformBuffer();
    
    struct android_app* app;
    VulkanRenderer* renderer;
    Camera* camera;
    Player* player;
    
    float deltaTime;
    long lastFrameTime;
    float totalTime;
    
    bool touchActive;
    float lastTouchX;
    float lastTouchY;
};

#endif
