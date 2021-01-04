//
// Created by nbdy on 03.01.21.
//

#include "PulldownBar.h"

void PulldownBar::loop() {
    UIItem::loop();
    drawPullbar();

    if(hitsLock(firstYLock)) y = firstYLock;
    else if(hitsLock(secondYLock)) y = secondYLock;
    else if(y < 1) y = 0;
    else y -= drawbackSpeed;
}

void PulldownBar::drawPullbar() {
    DrawRectangle(x, y, SCREEN_WIDTH, height, GREEN);
    DrawRectangle(x + lineThickness, y + lineThickness, SCREEN_WIDTH - lineThickness * 2, height - lineThickness * 2, BLACK);
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

