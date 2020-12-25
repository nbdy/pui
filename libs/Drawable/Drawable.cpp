//
// Created by nbdy on 25.12.20.
//

#include "Drawable.h"

Drawable::Drawable(): center(Vector2 {0, 0}), size(Vector2 {1, 1}) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    calculate();
}

Drawable::Drawable(Vector2 center, Vector2 size): center(center), size(size) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    calculate();
}

void Drawable::work() {}

void Drawable::draw() {}

bool Drawable::mouseOver() const {
    auto mp = GetMousePosition();
    return mp.x >= topLeft.x && mp.x <= bottomRight.x && mp.y >= topLeft.y && mp.y <= bottomRight.y;
}

Vector2 Drawable::calculateSize(Vector2 topLeft, Vector2 bottomRight) {
    return Vector2 {
        bottomRight.x - topLeft.x,
        bottomRight.y - topLeft.y
    };
}

Vector2 Drawable::calculateTopLeft(Vector2 center, Vector2 size) {
    return Vector2 {
        center.x - size.x / 2,
        center.y - size.y / 2
    };
}

Vector2 Drawable::calculateBottomRight(Vector2 center, Vector2 size) {
    return Vector2 {
        center.x + size.x / 2,
        center.y + size.y / 2
    };
}

Vector2 Drawable::calculateCenterFromTLS(Vector2 topLeft, Vector2 size) {
    return Vector2 {
            topLeft.x + size.x / 2,
            topLeft.y + size.y / 2
    };
}

Vector2 Drawable::calculateCenterFromBRS(Vector2 bottomRight, Vector2 size) {
    return Vector2 {
            bottomRight.x - size.x / 2,
            bottomRight.y - size.y / 2
    };
}

Vector2 Drawable::calculateSizeFromTLBR(Vector2 topLeft, Vector2 bottomRight) {
    return Vector2 {
            bottomRight.x - topLeft.x,
            bottomRight.y - topLeft.y
    };
}

Vector2 Drawable::calculateCenterFromTLBR(Vector2 topLeft, Vector2 bottomRight) {
    return Vector2 {
            topLeft.x + bottomRight.x / 2,
            topLeft.y + bottomRight.y / 2
    };
}

void Drawable::calculate() {
    topLeft = calculateTopLeft(center, size);
    bottomRight = calculateBottomRight(center, size);
}

Vector2 Drawable::getTopLeft() const {
    return topLeft;
}

Vector2 Drawable::getBottomRight() const {
    return bottomRight;
}

Vector2 Drawable::getCenter() const {
    return center;
}

Vector2 Drawable::getSize() const {
    return size;
}

void Drawable::setTopLeft(Vector2 value) {
    topLeft = value;
    center = calculateCenterFromTLS(topLeft, size);
    bottomRight = calculateBottomRight(center, size);
}

void Drawable::setBottomRight(Vector2 value) {
    bottomRight = value;
    center = calculateCenterFromBRS(bottomRight, size);
    topLeft = calculateTopLeft(center, size);
}

void Drawable::setCenter(Vector2 value) {
    center = value;
    topLeft = calculateTopLeft(center, size);
    bottomRight = calculateBottomRight(center, size);
}

void Drawable::setSize(Vector2 value) {
    size = value;
    center = calculateCenterFromTLS(topLeft, size);
    bottomRight = calculateBottomRight(center, size);
}

void Drawable::resize(Vector2 _center, Vector2 _size) {
    this->center = _center;
    this->size = _size;
    topLeft = calculateTopLeft(_center, _size);
    bottomRight = calculateBottomRight(_center, _size);
}
