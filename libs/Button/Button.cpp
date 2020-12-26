//
// Created by nbdy on 25.12.20.
//

#include "Button.h"

Button::Button(): Drawable(Vector2 {0, 0}, BUTTON_DEFAULT_SIZE), callback(onClickCallback), text("") {}

Button::Button(const char *text, Vector2 center): Drawable(center, BUTTON_DEFAULT_SIZE), callback(onClickCallback), text(text) {}

Button::Button(const char *text, Vector2 center, Vector2 size) : Drawable(center, size), callback(onClickCallback), text(text) {}

Button::Button(const char *text, Vector2 center, ButtonCallback callback, void* callbackCtx): Drawable(center, BUTTON_DEFAULT_SIZE),
callback(callback), text(text), callbackCtx(callbackCtx) {}

Button::Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void* callbackCtx): Drawable(center, size),
callback(callback), text(text), callbackCtx(callbackCtx) {}

Button::Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void* callbackCtx, Color outlineColor,
               Color infillColor, Color textColor): Drawable(center, size), callback(callback), outlineColor(outlineColor),
               infillColor(infillColor), textColor(textColor), text(text), callbackCtx(callbackCtx) {}

Button::Button(const char *text, Vector2 size, ButtonCallback callback, void *callbackCtx, int outlineThickness): Drawable(Vector2 {0, 0}, size),
text(text), callback(callback), callbackCtx(callbackCtx), outlineThickness(outlineThickness) {}

bool Button::clicked() {
    if(mouseOver() && mouseWasDown && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        mouseWasDown = false;
        return true;
    } else if(mouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) mouseWasDown = true;
    else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) mouseWasDown = false;
    return false;
}

void Button::onClickCallback(void* data) {
    LOG_F(WARNING, "Button::onClickCallback is not set");
}


void Button::draw() {
    DrawRectangle((int) topLeft.x, (int) topLeft.y, (int) size.x, (int) size.y, outlineColor);
    DrawRectangle((int) topLeft.x + outlineThickness, (int) topLeft.y + outlineThickness, (int) size.x - outlineThickness * 2, (int) size.y - outlineThickness * 2, infillColor);
    DrawText(text, (int) center.x - fontSize / 2,  center.y - (float) TextLength(text) / 2, fontSize, textColor);
}

void Button::work() {
    if(clicked() && mouseOver()) callback(callbackCtx);
}

Button::Button(const char *text, Vector2 center, Vector2 size, ButtonCallback callback, void *callbackCtx,
               int outlineThickness, Color outlineColor, Color infillColor, Color textColor): Drawable(center, size),
               text(text), callback(callback), callbackCtx(callbackCtx), outlineThickness(outlineThickness), outlineColor(outlineColor),
               infillColor(infillColor), textColor(textColor){

}
