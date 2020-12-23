//
// Created by nbdy on 23.12.20.
//

#include "Shortcut.h"

Shortcut::Shortcut(Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked): onClicked(onClicked), onLongClicked(onLongClicked):
topLeft(topLeft), height(50), width(50), onClicked(onClicked), onLongClicked(onLongClicked){

}
