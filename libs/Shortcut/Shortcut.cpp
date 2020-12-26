//
// Created by nbdy on 23.12.20.
//

#include "Shortcut.h"

Shortcut::Shortcut(const char *icon, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(onClicked, onLongClicked), icon(icon) {}

Shortcut::Shortcut(Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, 50, 50, onClicked, onLongClicked), icon(Utils::getIcon(RICON_NONE, "")) {}

Shortcut::Shortcut(Vector2 topLeft, float height, float width, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, height, width, onClicked, onLongClicked), icon(Utils::getIcon(RICON_NONE, "")){}

Shortcut::Shortcut(const char* icon, Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, 50, 50, onClicked, onLongClicked),
icon(icon) {}

void Shortcut::draw() {

}
