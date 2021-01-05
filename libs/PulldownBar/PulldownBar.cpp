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

PulldownBar::~PulldownBar() {
    // unloadTextures();
}

void PulldownBar::loadTextures() {
    texBrightnessLow = Utils::getIcon("brightnessLow", Vector2 {18, 18});
    texBrightnessHigh = Utils::getIcon("brightnessHigh", Vector2 {18, 18});
    texBattery = Utils::getIcon("battery", Vector2 {clockTextSize, clockTextSize});
    texBatteryCharging = Utils::getIcon("batteryCharging", Vector2 {clockTextSize, clockTextSize});
    texBatteryAlert = Utils::getIcon("batteryAlert", Vector2 {clockTextSize, clockTextSize});
}

void PulldownBar::unloadTextures() {
    UnloadTexture(texBrightnessLow);
    UnloadTexture(texBrightnessHigh);
    UnloadTexture(texBattery);
    UnloadTexture(texBatteryCharging);
    UnloadTexture(texBatteryAlert);
}

void PulldownBar::onClicked() {
    // for silence
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
    DrawRectangle(x, y, SCREEN_WIDTH, height, Color {15, 235, 25, 42});
    DrawRectangle(x + lineThickness, y + lineThickness, SCREEN_WIDTH - lineThickness * 2, height - lineThickness * 2, Color {20, 20, 20, 200});
    DrawRectangle(0, 0, SCREEN_WIDTH, y, Color {20, 20, 20, 128});

    if(y >= 0) {
        drawClock(8, height / 2);
        drawBattery(SCREEN_WIDTH - 32, height / 2);
    }
    if(y >= firstYLock / 2) {
        drawDate(8, height * 2);
    }
    if(y >= firstYLock) {

    }
    if(y >= secondYLock) {
        drawBrightnessSlider(0, height * 3);
    }

}

// todo remove 8, 36, 50, 100 and replace with vars
void PulldownBar::drawBrightnessSlider(float x, float y) {
    if(GuiImageButton(Rectangle {x + 8, y, 36, 36}, "", texBrightnessLow)) brightnessSliderValue = 10;
    brightnessSliderValue = GuiSlider(Rectangle {x + 50, y, SCREEN_WIDTH - 100, 36}, "", "", brightnessSliderValue, 0, 250);
    if(GuiImageButton(Rectangle {SCREEN_WIDTH - 8 - 36, y, 36, 36}, "", texBrightnessHigh)) brightnessSliderValue = 250;
}

void PulldownBar::drawClock(float x, float y) const {
    DrawText(Utils::getTimestamp(clockTextFormat).c_str(), x, y - clockTextSize / 2, clockTextSize, GREEN);
}

void PulldownBar::drawDate(float x, float y) {
    DrawText(Utils::getTimestamp(dateTextFormat).c_str(), x, y - dateTextSize / 2, 12, GREEN);
}

void PulldownBar::drawBattery(float x, float y) {
    auto c = Utils::getBatteryCapacity();
    auto v = std::to_string(c);
    y = y - clockTextSize / 2;
    x -= clockTextSize;
    DrawText(v.c_str(), x + clockTextSize, y, clockTextSize, GREEN);
    if(Utils::isBatteryCharging()) DrawTexture(texBatteryCharging, x, y, GREEN);
    else if(c > 20) DrawTexture(texBattery, x, y, GREEN);
    else DrawTexture(texBatteryAlert, x, y, GREEN);
}
