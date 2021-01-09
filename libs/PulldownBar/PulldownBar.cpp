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
}

void PulldownBar::unloadTextures() {
}

void PulldownBar::onClicked() {
    // for silence
}

void PulldownBar::onLongClicked() {

}

bool PulldownBar::wasClicked() {

}

bool PulldownBar::hitsLock(float lock) {
    return lock - drawbackSpeed <= y && lock + drawbackSpeed >= y;
}

void PulldownBar::loop() {
    UIItem::loop();


    drawPullbar();
}

void PulldownBar::drawPullbar() {

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

}

void PulldownBar::drawClock(float x, float y) const {

}

void PulldownBar::drawDate(float x, float y) {

}

void PulldownBar::drawBattery(float x, float y) {
    auto c = Utils::getBatteryCapacity();
    auto v = std::to_string(c);
    y = y - clockTextSize / 2;
    x -= clockTextSize;

}
