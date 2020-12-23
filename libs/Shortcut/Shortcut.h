//
// Created by nbdy on 23.12.20.
//

#ifndef PUI_SHORTCUT_H
#define PUI_SHORTCUT_H

#include <Widget/Widget.h>

class Shortcut : public Widget {
public:
    Shortcut(Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked);
};


#endif //PUI_SHORTCUT_H
