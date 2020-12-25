//
// Created by nbdy on 23.12.20.
//

#include "Widget.h"

Widget::Widget() {}

/*
Widget::Widget(json state) {
    state.get<WidgetState>();
}

Widget::Widget(const json &state, callbackFunction onClicked, callbackFunction onLongClicked): state(state.get<WidgetState>()), onClicked(onClicked), onLongClicked(onLongClicked) {}

Widget::Widget(const json &state, callbackFunction onClicked): state(state.get<WidgetState>()), onClicked(onClicked) {}
*/

Widget::Widget(callbackFunction onClicked, callbackFunction onLongClicked): state(WidgetState {
    Vector2 {0, 0},
    Vector2 {50, 50},
    false,
    false
}), onClicked(onClicked), onLongClicked(onLongClicked) {

}

Widget::Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked): state(WidgetState {
    topLeft, bottomRight, false, false
}), onClicked(onClicked){}

Widget::Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked): state(WidgetState {
    topLeft, bottomRight, false, false
}), onClicked(onClicked), onLongClicked(onLongClicked){}

Widget::Widget(Vector2 topLeft, float height, float width, callbackFunction onClicked): state(WidgetState {
    topLeft, Vector2 {topLeft.x + height, topLeft.y + width},
}), onClicked(onClicked) {}

Widget::Widget(Vector2 topLeft, float height, float width, callbackFunction onClicked, callbackFunction onLongClicked): state(WidgetState {
    topLeft, Vector2 {topLeft.x + height, topLeft.y + width}
}), onClicked(onClicked), onLongClicked(onLongClicked) {}

void Widget::work() {
    if(state.enabled) {
        wasClicked();
        draw();
    }
}

void Widget::wasClicked() {
    if(!mouseOnWidget()) return;

    if(clickedTimePoint != -1) {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clickedTimePoint = std::time(nullptr);
    } else {
        auto clickedDuration = std::time(nullptr) - clickedTimePoint;
        if(clickedDuration >= state.onLongClickThreshold) onLongClicked();
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) onClicked();
        clickedTimePoint = -1;
    }
}

void Widget::draw() {

}

WidgetState Widget::getState() {
    return state;
}

bool Widget::mouseOnWidget() const {
    auto mp = GetMousePosition();
    auto hy = state.size.y / 2;
    auto hx = state.size.x / 2;
    return (mp.x <= state.center.x - hx  && mp.x >= state.center.x + hx) && (mp.y <= state.center.y - hy && mp.y >= state.center.y + hy);
}

/*
json Widget::getStateJson() {
    return state;
}
*/

Widget::~Widget() = default;
