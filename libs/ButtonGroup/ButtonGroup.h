//
// Created by nbdy on 25.12.20.
//

#ifndef GPS_BUTTONGROUP_H
#define GPS_BUTTONGROUP_H

#include <vector>

#include <loguru/loguru.hpp>

#include <Button/Button.h>

typedef std::vector<Button> Buttons;

class ButtonGroup : public Drawable {
protected:
    Buttons buttons;

    float padding = 8;

public:
    ButtonGroup();
    ButtonGroup(Vector2 center, Vector2 size, Buttons buttons);
    ButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding);

    void draw() override;
    void work() override;

    virtual Vector2 calculateSize();
};

class HButtonGroup : public ButtonGroup {
public:
    HButtonGroup();
    HButtonGroup(Vector2 center, Vector2 size, Buttons buttons);
    HButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding);

    void draw() override;
    Vector2 calculateSize() override;
};

class VButtonGroup : public ButtonGroup {
public:
    VButtonGroup();
    VButtonGroup(Vector2 center, Vector2 size, Buttons buttons);
    VButtonGroup(Vector2 center, Vector2 size, Buttons buttons, float padding);

    void draw() override;
    Vector2 calculateSize() override;
};


#endif //GPS_BUTTONGROUP_H
