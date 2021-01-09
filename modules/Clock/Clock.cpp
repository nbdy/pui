//
// Created by nbdy on 31.12.20.
//

#include <BaseModule/BaseModule.h>
#include <Manager/Manager.h>

class Clock : public BaseModule {
public:
    Clock() {};

    ~Clock() override {
    }

    bool work(void *data, const context &ctx) override {
        return true;
    }

    void loop(void *data) override {

    }

    void backButtonClicked(void *data) override {
        ((Manager*) data)->setCurrentModule(nullptr);
    }
};

class ClockWidget : public BaseWidget {
public:
    explicit ClockWidget(Clock* clock): BaseWidget() {};
};

extern "C" tModule* create() {
    return dynamic_cast<Clock*>(new Clock);
};