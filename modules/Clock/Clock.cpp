//
// Created by nbdy on 31.12.20.
//

#include <BaseModule/BaseModule.h>

class Clock : public BaseModule {
public:
    Clock(): BaseModule("Clock", "Simple clock with a widget", "0.1",
                        "/home/nbdy/CLionProjects/pui/modules/Clock/icon.png",
                        UI, false) {};

    ~Clock() override {
        UnloadTexture(shortcut);
    }

    bool work(void *data, const context &ctx) override {
        return true;
    }

    void loop(void *data) override {
        ClearBackground(BLACK);
        DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 8, GREEN);
    }
};

extern "C" BaseModule* create() {
    return static_cast<BaseModule*>(new Clock);
};