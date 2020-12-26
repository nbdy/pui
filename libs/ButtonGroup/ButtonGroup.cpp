//
// Created by nbdy on 25.12.20.
//

#include "ButtonGroup.h"

#include <utility>

ButtonGroup::ButtonGroup(): Drawable(Vector2 {0, 0}, Vector2 {1, 1}) {}

ButtonGroup::ButtonGroup(Vector2 center, Vector2 size, Buttons buttons): Drawable(center, size), buttons(std::move(buttons)) {}

ButtonGroup::ButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding): Drawable(center, size), buttons(std::move(buttons)), padding(padding) {}

void ButtonGroup::draw() {
    LOG_F(WARNING, "ButtonGroup::draw should be overwritten");
}

void ButtonGroup::work() {
    for(auto btn : buttons) btn.work();
}

Vector2 ButtonGroup::calculateSize() {
    LOG_F(WARNING, "ButtonGroup::calculateSize should be overwritten");
    return Vector2();
}

// HButtonGroup -----------------------------------------------------------------------------------

HButtonGroup::HButtonGroup() {}

HButtonGroup::HButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding) : ButtonGroup(center, size, std::move(buttons), padding) {}

HButtonGroup::HButtonGroup(Vector2 center, Vector2 size, Buttons buttons) : ButtonGroup(center, size, std::move(buttons)) {}

void HButtonGroup::draw() {
    auto nextBtnPos = getTopLeft();
    for(auto& btn : buttons) {
        btn.setTopLeft(nextBtnPos);
        nextBtnPos.x += (btn.getSize().x + padding);
        btn.draw();
    }
}

Vector2 HButtonGroup::calculateSize() {
    Vector2 r {0, 0};
    for(const auto& btn : buttons) {
        auto btnSize = btn.getSize();
        if(r.x < btnSize.x) r.x = btnSize.x;
        r.y += btnSize.y + padding;
    }
    r.y -= padding;
    return r;
}

// VButtonGroup -----------------------------------------------------------------------------------

VButtonGroup::VButtonGroup() {}

VButtonGroup::VButtonGroup(Vector2 center, Vector2 size, Buttons buttons) : ButtonGroup(center, size, std::move(buttons)) {}

VButtonGroup::VButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding) : ButtonGroup(center, size, std::move(buttons), padding) {}

void VButtonGroup::draw() {
    auto nextBtnPos = getTopLeft();
    for(auto& btn : buttons) {
        btn.setTopLeft(nextBtnPos);
        nextBtnPos.y += btn.getSize().y;
        btn.draw();
    }
}

Vector2 VButtonGroup::calculateSize() {
    Vector2 r;
    for(const auto& btn : buttons) {
        auto btnSize = btn.getSize();
        if(r.y < btnSize.y) r.y = btnSize.y;
        r.x += btnSize.x + padding;
    }
    r.x -= padding;
    return r;
}
