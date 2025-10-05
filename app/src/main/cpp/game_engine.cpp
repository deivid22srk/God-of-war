#include "game_engine.h"
#include <android/log.h>
#include <time.h>
#include <cmath>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "GameEngine", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "GameEngine", __VA_ARGS__))

GameEngine::GameEngine(struct android_app* app)
    : app(app)
    , renderer(nullptr)
    , camera(nullptr)
    , player(nullptr)
    , deltaTime(0.0f)
    , lastFrameTime(0)
    , totalTime(0.0f)
    , touchActive(false)
    , lastTouchX(0.0f)
    , lastTouchY(0.0f) {
}

GameEngine::~GameEngine() {
    if (player) delete player;
    if (camera) delete camera;
    if (renderer) delete renderer;
}

bool GameEngine::initialize() {
    LOGI("Initializing Game Engine...");
    
    renderer = new VulkanRenderer(app->window);
    if (!renderer->initialize()) {
        LOGE("Failed to initialize renderer");
        return false;
    }
    
    float aspect = (float)renderer->getWidth() / (float)renderer->getHeight();
    camera = new Camera(aspect);
    camera->setPosition(0.0f, 1.5f, 5.0f);
    camera->lookAt(0.0f, 0.0f, 0.0f);
    
    player = new Player();
    player->setPosition(0.0f, 0.0f, 0.0f);
    
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    lastFrameTime = now.tv_sec * 1000000000LL + now.tv_nsec;
    
    LOGI("Game Engine initialized successfully");
    return true;
}

void GameEngine::update() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    long currentTime = now.tv_sec * 1000000000LL + now.tv_nsec;
    deltaTime = (currentTime - lastFrameTime) / 1000000000.0f;
    lastFrameTime = currentTime;
    totalTime += deltaTime;
    
    player->update(deltaTime);
    camera->update(deltaTime);
    
    float radius = 5.0f;
    float camX = sin(totalTime * 0.3f) * radius;
    float camZ = cos(totalTime * 0.3f) * radius;
    camera->setPosition(camX, 2.0f, camZ);
    camera->lookAt(0.0f, 0.0f, 0.0f);
}

void GameEngine::render() {
    updateUniformBuffer();
    
    UniformBufferObject ubo = {};
    
    float model[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    memcpy(ubo.model, model, sizeof(model));
    camera->getViewMatrix(ubo.view);
    camera->getProjectionMatrix(ubo.proj);
    
    ubo.lightPos[0] = 5.0f;
    ubo.lightPos[1] = 5.0f;
    ubo.lightPos[2] = 5.0f;
    ubo.lightPos[3] = 1.0f;
    
    float camPos[3];
    camera->getPosition(camPos);
    ubo.viewPos[0] = camPos[0];
    ubo.viewPos[1] = camPos[1];
    ubo.viewPos[2] = camPos[2];
    ubo.viewPos[3] = 1.0f;
    
    renderer->drawFrame(ubo);
}

void GameEngine::handleTouch(int32_t action, float x, float y) {
    const int32_t AMOTION_EVENT_ACTION_DOWN = 0;
    const int32_t AMOTION_EVENT_ACTION_UP = 1;
    const int32_t AMOTION_EVENT_ACTION_MOVE = 2;
    
    if (action == AMOTION_EVENT_ACTION_DOWN) {
        touchActive = true;
        lastTouchX = x;
        lastTouchY = y;
    } else if (action == AMOTION_EVENT_ACTION_UP) {
        touchActive = false;
    } else if (action == AMOTION_EVENT_ACTION_MOVE && touchActive) {
        float deltaX = x - lastTouchX;
        float deltaY = y - lastTouchY;
        
        camera->rotate(deltaY * 0.01f, deltaX * 0.01f);
        
        lastTouchX = x;
        lastTouchY = y;
    }
}

void GameEngine::updateUniformBuffer() {
}
