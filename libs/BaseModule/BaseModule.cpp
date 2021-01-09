//
// Created by nbdy on 20.12.20.
//

#include "BaseModule.h"

#include <utility>

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
