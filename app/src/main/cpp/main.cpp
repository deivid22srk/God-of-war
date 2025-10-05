#include <android_native_app_glue.h>
#include <android/log.h>
#include "game_engine.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "GodOfWar", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "GodOfWar", __VA_ARGS__))

struct AppState {
    struct android_app* app;
    GameEngine* engine;
    bool initialized;
    bool visible;
};

static void handleAppCmd(struct android_app* app, int32_t cmd) {
    AppState* state = (AppState*)app->userData;
    
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (state->app->window != nullptr) {
                LOGI("APP_CMD_INIT_WINDOW");
                state->engine = new GameEngine(state->app);
                if (state->engine->initialize()) {
                    state->initialized = true;
                    LOGI("Game engine initialized successfully");
                } else {
                    LOGE("Failed to initialize game engine");
                }
            }
            break;
            
        case APP_CMD_TERM_WINDOW:
            LOGI("APP_CMD_TERM_WINDOW");
            if (state->engine) {
                delete state->engine;
                state->engine = nullptr;
            }
            state->initialized = false;
            break;
            
        case APP_CMD_GAINED_FOCUS:
            LOGI("APP_CMD_GAINED_FOCUS");
            state->visible = true;
            break;
            
        case APP_CMD_LOST_FOCUS:
            LOGI("APP_CMD_LOST_FOCUS");
            state->visible = false;
            break;
            
        case APP_CMD_START:
            LOGI("APP_CMD_START");
            break;
            
        case APP_CMD_RESUME:
            LOGI("APP_CMD_RESUME");
            break;
            
        case APP_CMD_PAUSE:
            LOGI("APP_CMD_PAUSE");
            break;
            
        case APP_CMD_STOP:
            LOGI("APP_CMD_STOP");
            break;
    }
}

static int32_t handleInput(struct android_app* app, AInputEvent* event) {
    AppState* state = (AppState*)app->userData;
    
    if (!state->engine || !state->initialized) {
        return 0;
    }
    
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        int32_t action = AMotionEvent_getAction(event);
        float x = AMotionEvent_getX(event, 0);
        float y = AMotionEvent_getY(event, 0);
        
        state->engine->handleTouch(action, x, y);
        return 1;
    }
    
    return 0;
}

void android_main(struct android_app* app) {
    LOGI("God of War 2018 - Starting...");
    
    AppState state = {};
    state.app = app;
    state.initialized = false;
    state.visible = false;
    
    app->userData = &state;
    app->onAppCmd = handleAppCmd;
    app->onInputEvent = handleInput;
    
    while (true) {
        int events;
        struct android_poll_source* source;
        
        while (ALooper_pollAll(state.initialized && state.visible ? 0 : -1, nullptr, &events, (void**)&source) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
            
            if (app->destroyRequested != 0) {
                LOGI("Destroy requested");
                if (state.engine) {
                    delete state.engine;
                }
                return;
            }
        }
        
        if (state.initialized && state.visible && state.engine) {
            state.engine->update();
            state.engine->render();
        }
    }
}
