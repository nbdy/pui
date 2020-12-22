//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

BaseModule::BaseModule() = default;

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
    return "BaseModule";
}

std::string BaseModule::getDescription() {
    return "The BaseModule on which everything is based on.";
}

uint8_t BaseModule::getType() {
    return ModuleTypes::UI;
}

bool BaseModule::work() {
    return false;
}

