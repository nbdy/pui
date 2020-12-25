//
// Created by nbdy on 25.12.20.
//

#ifndef GPS_BUTTON_H
#define GPS_BUTTON_H

#include <loguru/loguru.hpp>

#include <Drawable/Drawable.h>

#define BUTTON_DEFAULT_SIZE Vector2 {50, 100}

typedef void (*ButtonCallback)(void*);

// todo long click
class Button : public Drawable {
    bool mouseWasDown = false;

    void *callbackCtx;
    ButtonCallback callback;

    Color outlineColor = GREEN;
    Color infillColor = BLACK;
    Color textColor = GREEN;

    int fontSize = 16;
    int outlineThickness = 4;

    const char* text;

protected:
    virtual bool clicked();
    static void onClickCallback(void* data);

public:
    Button();
    Button(const char *text, Vector2 size, ButtonCallback callback, void* callbackCtx, int outlineThickness);
    explicit Button(const char *text, Vector2 center);
    Button(const char *text, Vector2 center, ButtonCallback callback, void* callbackCtx);
    Button(const char *text, Vector2 center, Vector2 size);
    Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void* callbackCtx);
    Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void* callbackCtx, Color outlineColor, Color infillColor, Color textColor);
    Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void* callbackCtx, int outlineThickness, Color outlineColor, Color infillColor, Color textColor);

    void draw() override;
    void work() override;
};


#endif //GPS_BUTTON_H
