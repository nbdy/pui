//
// Created by nbdy on 23.12.20.
//

#ifndef PUI_WIDGET_H
#define PUI_WIDGET_H

#include <chrono>

#include <raylib.h>

#include <json.h>

#define NOW std::chrono::system_clock::now

typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> msecTimePoint;
typedef void (*callbackFunction)();

using json = nlohmann::json;

namespace pui {
    struct WidgetState {
        Vector2 topLeft;
        Vector2 bottomRight;
        bool enabled;
        int onLongClickThreshold;
    };
}

class Widget {
protected:
    pui::WidgetState state;

    bool clicked;
    msecTimePoint *clickedTimePoint = nullptr;

    callbackFunction onClicked;
    callbackFunction onLongClicked;

public:
    Widget();
    explicit Widget(const json& state);
    Widget(const json& state, callbackFunction onClicked);
    Widget(const json& state, callbackFunction onClicked, callbackFunction onLongClicked);
    Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked);
    Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked);
    Widget(Vector2 topLeft, Vector2 bottomRight, callbackFunction onClicked, callbackFunction onLongClicked, int onLongClickThreshold);
    Widget(Vector2 topLeft, int height, int width, callbackFunction onClicked);
    Widget(Vector2 topLeft, int height, int width, callbackFunction onClicked, callbackFunction onLongClicked);

    void work();
    virtual bool wasClicked();
    virtual void draw();

    pui::WidgetState getState();
    json getStateJson();

    [[nodiscard]] bool mouseOnWidget() const;

    ~Widget();
};


#endif //PUI_WIDGET_H
