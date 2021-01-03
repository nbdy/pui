//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

#include <utility>

BaseModule::BaseModule(): type(BACKGROUND), sharing(true), shortcut(LoadTextureFromImage(GenImageColor(96, 96, GREEN))) {}

BaseModule::BaseModule(std::string name, std::string description, std::string version):
name(std::move(name)), description(std::move(description)), version(std::move(version)), type(BACKGROUND), sharing(true){}

BaseModule::BaseModule(std::string name, std::string description, std::string version, const std::string& shortcutPath):
name(std::move(name)), description(std::move(description)), version(std::move(version)), shortcut(LoadTexture(shortcutPath.c_str())),
type(UI), sharing(false){}

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

bool BaseModule::isSharing() const {
    return sharing;
}

shareMap BaseModule::getShareMap() {
    return shareMap();
}

bool BaseModule::shortcutClicked(Rectangle bounds, const char* text) {
    return GuiImageButton(bounds, text, shortcut);
}

void BaseModule::backButtonClicked(void* data) {

}

void BaseModule::setError(const std::string& msg) {
    error = true;
    errorMessage = msg;
}

bool BaseModule::hasError() const {
    return error;
}

std::string BaseModule::getErrorMessage() {
    return errorMessage;
}

void BaseModule::deallocate() {
    delete this;
}

void BaseModule::drawWidget(void *data) {
    widget->loop(data);
}

BaseModule::~BaseModule() = default;

// ----------------------------------------------------------------------------------------
// BaseWidget
// ----------------------------------------------------------------------------------------
BaseWidget::BaseWidget() = default;

BaseWidget::BaseWidget(Rectangle bounds, ptModule module): bounds(bounds), module(module) {}

BaseWidget::~BaseWidget() = default;

bool BaseWidget::onClicked() {
    return false;
}

bool BaseWidget::onLongClicked() {
    return false;
}

void BaseWidget::loop(void *data) {

}

void BaseWidget::work(context ctx, void *data) {

}
