//
// Created by nbdy on 03.01.21.
//

#include "PulldownBar.h"

PulldownBar::PulldownBar(): UIItem(0, 0, 20, SCREEN_WIDTH, 42) {
    loadTextures();
}

PulldownBar::PulldownBar(modVec modules): UIItem(0, 0, 20, SCREEN_WIDTH, 42), modules(std::move(modules)) {
    loadTextures();
}

void PulldownBar::loadTextures() {
    texBrightnessLow = Utils::getIcon("brightnessLow", Vector2 {18, 18});
    texBrightnessHigh = Utils::getIcon("brightnessHigh", Vector2 {18, 18});
}

void PulldownBar::onLongClicked() {
    y = GetMouseY() - height / 2;
}

bool PulldownBar::wasClicked() {
    return UIItem::wasClicked() || (clicked != 0 && IsMouseButtonDown(MOUSE_LEFT_BUTTON));
}

bool PulldownBar::hitsLock(float lock) {
    return lock - drawbackSpeed <= y && lock + drawbackSpeed >= y;
}

void PulldownBar::loop() {
    UIItem::loop();

    if(!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(hitsLock(firstYLock)) y = firstYLock;
        else if(hitsLock(secondYLock)) y = secondYLock;
        else if(y < 1) y = 0;
        else y -= drawbackSpeed;
    }

    drawPullbar();
}

void PulldownBar::drawPullbar() {
    DrawRectangle(x, y, SCREEN_WIDTH, height, GREEN);
    DrawRectangle(x + lineThickness, y + lineThickness, SCREEN_WIDTH - lineThickness * 2, height - lineThickness * 2, BLACK);

    if(y >= 0) {
        drawClock(8, height / 2);
    } else if(y >= firstYLock) {
        drawClock(8, height / 2);
    } else if(y >= secondYLock) {
        drawBrightnessSlider();
    }

}

void PulldownBar::drawBrightnessSlider() {
    if(GuiImageButton(Rectangle {x + 10, brightnessSliderYOffset, 36, 36}, "", texBrightnessLow)) brightnessSliderValue = 10;
    brightnessSliderValue = GuiSlider(Rectangle {x + 50, brightnessSliderYOffset, SCREEN_WIDTH - 100, 36}, "", "", brightnessSliderValue, 0, 250);
    if(GuiImageButton(Rectangle {SCREEN_WIDTH - 10 - 36, brightnessSliderYOffset, 36, 36}, "", texBrightnessHigh)) brightnessSliderValue = 250;
}

void PulldownBar::drawClock(float x, float y) const {
    DrawText(Utils::getTimestamp(clockTextFormat).c_str(), x, y - clockTextSize / 2, clockTextSize, GREEN);
}

void PulldownBar::drawDate(float x, float y) {
    DrawText(Utils::getTimestamp("%a., %d. %b.").c_str(), x, y - 6, 12, GREEN);
}

void PulldownBar::onClicked() {
    // for silence
}
