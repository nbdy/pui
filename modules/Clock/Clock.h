//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_CLOCK_H
#define PUI_CLOCK_H

#include <Shortcut/Shortcut.h>
#include <BaseModule/BaseModule.h>

class ClockWidget : public Widget {
public:
    ClockWidget(callbackFunction onClicked, callbackFunction onLongClicked):
    Widget(onClicked, onLongClicked) {}
};

class ClockShortcut : public Shortcut {
public:
    ClockShortcut(callbackFunction onClicked, callbackFunction onLongClicked):
    Shortcut(GuiIconText(RICON_CLOCK, "Clock"), Vector2 {0, 0}, onClicked, onLongClicked){}
};

class Clock : public BaseModule {
protected:
    virtual void onWidgetClicked() {
        // todo open module view
    }

    virtual void onWidgetLongClicked() {
        // todo make widget slightly jiggly and move/resizeable
    }

    virtual void onShortcutClicked() {

    }

    virtual void onShortcutLongClicked() {

    }

public:
    Clock():
    type(UI), sharing(false), version("0.1"), description("Simple clock with widget"), name("Clock"),
    widget(new ClockWidget(onWidgetClicked, onWidgetLongClicked)),
    shortcut(new ClockShortcut(onShortcutClicked, onShortcutLongClicked)){}

    bool work(const context &ctx) override {

    }
};

extern "C" Clock* create() {
    return new Clock();
};


#endif //PUI_CLOCK_H
