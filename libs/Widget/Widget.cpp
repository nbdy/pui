//
// Created by nbdy on 23.12.20.
//

#include "Widget.h"

Widget::Widget() {}

Widget::Widget(const json& state): state(state.get<pui::WidgetState>()) {}

Widget::Widget(const json &state, callbackFunction onClicked, callbackFunction onLongClicked): state(state.get<pui::WidgetState>()), onClicked(onClicked), onLongClicked(onLongClicked) {}

Widget::Widget(const json &state, callbackFunction onClicked): state(state.get<pui::WidgetState>()), onClicked(onClicked) {}

Widget::Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked):
topLeft(topLeft), bottomRight(bottomRight), onClicked(onClicked){}

Widget::Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked):
topLeft(topLeft), bottomRight(bottomRight), onClicked(onClicked), onLongClicked(onLongClicked){}

Widget::Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked, int onLongClickThreshold):
               topLeft(topLeft), bottomRight(bottomRight), onClicked(onClicked), onLongClicked(onLongClicked), onLongClickThreshold(onLongClickThreshold){}

Widget::Widget(Vector2 topLeft, int height, int width, callbackFunction onClicked):
topLeft(topLeft), bottomRight(Vector2 {topLeft.x + height, topLeft.y + width}), onClicked(onClicked) {}

Widget::Widget(Vector2 topLeft, int height, int width, callbackFunction onClicked, callbackFunction onLongClicked):
topLeft(topLeft), bottomRight(Vector2 {topLeft.x + height, topLeft.y + width}), onClicked(onClicked), onLongClicked(onLongClicked) {}

void Widget::work() {
    if(enabled) {
        wasClicked();
        draw();
    }
}

bool Widget::wasClicked() {
    if(!mouseOnWidget()) return;

    if(clickedTimePoint == nullptr) {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clickedTimePoint = NOW();
        }
    } else {
        auto clickedDuration = NOW() - clickedDuration;
        if(clickedDuration >= state.onLongClickThreshold) {
            onLongClicked();
            clickedTimePoint = nullptr;
            return;
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            onClicked();
            clickedTimePoint = nullptr;
        }
    }
}

void Widget::draw() {

}

bool Widget::mouseOnWidget() const {
    auto mp = GetMousePosition();
    return (mp.x > state.topLeft.x && mp.x < state.bottomRight.x && mp.y > state.topLeft.y && mp.y < state.bottomRight.y);
}

pui::WidgetState Widget::getState() {
    return state;
}

json Widget::getStateJson() {
    return state;
}

Widget::~Widget() = default;
