//
// Created by nbdy on 23.12.20.
//

#include <cstring>
#include "Shortcut.h"

Shortcut::Shortcut(const char *icon, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(onClicked, onLongClicked), icon(icon) {}

Shortcut::Shortcut(Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, 50, 50, onClicked, onLongClicked), icon(GuiIconText(RICON_NONE, "")) {}

Shortcut::Shortcut(Vector2 topLeft, float height, float width, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, height, width, onClicked, onLongClicked), icon(GuiIconText(RICON_NONE, "")){}

Shortcut::Shortcut(const char* icon, Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked):
Widget(topLeft, 50, 50, onClicked, onLongClicked),
icon(icon) {}

void Shortcut::draw() {

}

// ripped out of raygui so we can just use ricons
const char *Shortcut::GuiIconText(int iconId, const char *text) {
    static char buffer[1024] = { 0 };
    memset(buffer, 0, 1024);

    sprintf(buffer, "#%03i#", iconId);

    if (text != nullptr){
        for (int i = 5; i < 1024; i++){
            buffer[i] = text[i - 5];
            if (text[i - 5] == '\0') break;
        }
    }

    return buffer;
}
