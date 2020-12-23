//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_CLOCK_H
#define PUI_CLOCK_H

#include <Widget/Widget.h>
#include <BaseModule/BaseModule.h>

class ClockWidget : public Widget {
public:
    ClockWidget(callbackFunction onClicked, callbackFunction onLongClicked):
    topLeft(Vector2{0, 0}), bottomRight(Vector2{50, 100}), onClicked(onClicked), onLongClicked(onLongClicked),
    {}
};

class Clock : public BaseModule {
protected:
    virtual void onWidgetClicked() {
        // todo open module view
    }

    virtual void onWidgetLongClicked() {
        // todo make widget slightly jiggly and move/resizeable
    }

public:
    Clock(): type(UI), sharing(false), version("0.1"), description("Simple clock with widget"), name("Clock"), widget(new ClockWidget(onWidgetClicked, onWidgetLongClicked)) {

    }

    bool work(const context &ctx) override {

    }
};

extern "C" Clock* create() {
    return new Clock();
};


#endif //PUI_CLOCK_H
