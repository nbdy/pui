//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

BaseModule::BaseModule(): type(UI), sharing(false){}

extern "C" BaseModule* create() {
    return new BaseModule();
}

bool BaseModule::drawWidget(int x, int y) {
    return false;
}

void BaseModule::drawModule() {

}

std::string BaseModule::getVersion() {
    return "0";
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

