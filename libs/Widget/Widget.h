//
// Created by nbdy on 23.12.20.
//

#ifndef PUI_WIDGET_H
#define PUI_WIDGET_H

#include <ctime>

#include <raylib.h>

#include <Utils/Utils.h>

#define NOT_CLICKED Vector2 {-1, -1}

typedef void (*callbackFunction)();

// todo saving
struct WidgetState {
    Vector2 center = Vector2 {(float) SCREEN_HEIGHT / 2, (float) SCREEN_WIDTH / 2};
    Vector2 size = Vector2 { 0.0, 0.0};

    bool mousePressed = false;

    Vector2 clicked() {
        bool _mouseDown = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        if(mousePressed != _mouseDown) {
            mousePressed = !mousePressed;
            auto mp = GetMousePosition();
            if((mp.x <= center.x - size.x / 2 && mp.x >= center.x + size.x) && (mp.y <= center.y - size.y / 2 && mp.y >= center.y + size.y)) return mp;
        }
        return NOT_CLICKED;
    }

    bool enabled = false;
    int onLongClickThreshold = 500;
};

class Widget {
protected:
    WidgetState state;

    bool clicked = false;
    time_t clickedTimePoint = -1;

    callbackFunction onClicked;
    callbackFunction onLongClicked;

public:
    Widget();
    /* todo
    explicit Widget(const json& state);
    Widget(const json& state, callbackFunction onClicked);
    Widget(const json& state, callbackFunction onClicked, callbackFunction onLongClicked);
    */
    Widget(callbackFunction onClicked, callbackFunction onLongClicked);
    Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked);
    Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked);
    Widget(Vector2 topLeft, float height, float width, callbackFunction onClicked);
    Widget(Vector2 topLeft, float height, float width, callbackFunction onClicked, callbackFunction onLongClicked);

    void work();
    virtual void wasClicked();
    virtual void draw();

    WidgetState getState();
    // json getStateJson(); // todo

    [[nodiscard]] bool mouseOnWidget() const;

    ~Widget();
};


#endif //PUI_WIDGET_H
