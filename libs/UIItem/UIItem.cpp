//
// Created by nbdy on 03.01.21.
//

#include "UIItem.h"

UIItem::UIItem() = default;

UIItem::UIItem(float x, float y, float height, float width): x(x), y(y), height(height), width(width) {}

UIItem::UIItem(float x, float y, float height, float width, long longClickThreshold): x(x), y(y), height(height), width(width), longClickThreshold(longClickThreshold) {}

UIItem::~UIItem() = default;

void UIItem::loop() {
    auto wc = wasClicked();
    if(wc) {
        if(firstClicked == 0) firstClicked = Utils::getTimestampLong();
        else {
            clicked = Utils::getTimestampLong();
            if(wasLongClicked()) onLongClicked();
        }
    } else {
        if(firstClicked != 0) onClicked();
        firstClicked = 0;
        clicked = 0;
    }
}

bool UIItem::wasClicked() {

}

bool UIItem::wasLongClicked() const {
    auto r = clicked - firstClicked;
    // LOG_F(INFO, "V : T - %li : %li", r, longClickThreshold);
    return r >= longClickThreshold;
}

float UIItem::getHeight() const {
    return height;
}

float UIItem::getWidth() const {
    return width;
}




