//
// Created by nbdy on 23.12.20.
//

#ifndef PUI_SHORTCUT_H
#define PUI_SHORTCUT_H

#include <Widget/Widget.h>
#include <BaseModule/BaseModule.h>

class Shortcut : public Widget {
protected:
    const char* icon;

public:
    Shortcut(const char* icon, callbackFunction onClicked, callbackFunction onLongClicked);
    Shortcut(Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked);
    Shortcut(Vector2 topLeft, float height, float width, callbackFunction onClicked, callbackFunction onLongClicked);
    Shortcut(const char* icon, Vector2 topLeft, callbackFunction onClicked, callbackFunction onLongClicked);

    virtual void draw() override;
};


#endif //PUI_SHORTCUT_H
