//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

#include <utility>

BaseModule::BaseModule(): type(UI), sharing(false), shortcut(LoadTextureFromImage(GenImageColor(96, 96, GREEN))) {}

BaseModule::BaseModule(std::string  name, std::string  description, std::string  version, const std::string& shortcutPath, ModuleTypes type, bool sharing):
name(std::move(name)), description(std::move(description)), version(std::move(version)),
type(type), sharing(sharing), shortcut(LoadTexture(shortcutPath.c_str())) {}

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

bool BaseModule::work(void* data, const context& ctx) {
    return false;
}

void BaseModule::loop(void *data) {

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

bool BaseModule::shortcutClicked(Rectangle bounds, const char* text) {
    return GuiImageButton(bounds, text, shortcut);
}

void BaseModule::backButtonClicked(void* data) {

}

BaseModule::~BaseModule() = default;
