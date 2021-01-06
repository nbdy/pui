//
// Created by nbdy on 31.12.20.
//

#include <BaseModule/BaseModule.h>
#include <Manager/Manager.h>

class Clock : public BaseModule {
public:
    Clock(): BaseModule("Clock", "Simple clock with a widget", "0.1",
                        "clock") {};

    ~Clock() override {
        UnloadTexture(shortcut);
    }

    bool work(void *data, const context &ctx) override {
        return true;
    }

    void loop(void *data) override {
        ClearBackground(BLACK);
        DrawText(Utils::getTimestamp(TIMESTAMP_FORMAT_HMS).c_str(), 20, 10, 72, GREEN);
    }

    void backButtonClicked(void *data) override {
        ((Manager*) data)->setCurrentModule(nullptr);
    }
};

class ClockWidget : public BaseWidget {
public:
    explicit ClockWidget(Clock* clock): BaseWidget(Rectangle {20, 20, SCREEN_WIDTH - 40, 400}, clock) {};
};

extern "C" tModule* create() {
    return dynamic_cast<Clock*>(new Clock);
};