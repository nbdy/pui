//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

BaseModule::BaseModule(): type(UI), sharing(false) {}

extern "C" BaseModule* create() {
    return new BaseModule();
}

std::string BaseModule::getVersion() {
    return version;
}

std::string BaseModule::getName() {
    return name;
}

std::string BaseModule::getDescription() {
    return description;
}

uint8_t BaseModule::getType() {
    return type;
}

bool BaseModule::work(const context& ctx) {
    return false;
}

bool BaseModule::isSharing() {
    return sharing;
}

shareMap BaseModule::getShareMap() {
    return shareMap();
}

bool BaseModule::isVisible() const {
    return visible;
}

void BaseModule::setVisible(bool value) {
    visible = value;
}

bool BaseModule::hasShortcut() {
    return shortcut == nullptr;
}

bool BaseModule::hasWidget() {
    return widget != nullptr;
}

std::shared_ptr<Widget> BaseModule::getWidget() {
    return widget;
}

std::shared_ptr<Shortcut> BaseModule::getShortcut() {
    return shortcut;
}
