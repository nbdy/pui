//
// Created by nbdy on 03.01.21.
//

#ifndef PUI_PULLDOWNBAR_H
#define PUI_PULLDOWNBAR_H

#include <UIItem/UIItem.h>
#include <Utils/Utils.h>

class PulldownBar : public UIItem {
protected:
    float drawbackSpeed = 16;
    float lineThickness = 2;
    float firstYLock = SCREEN_HEIGHT / 4;
    float secondYLock = SCREEN_HEIGHT / 1.2;

    void drawPullbar();

public:
    PulldownBar(): UIItem(0, 0, 20, SCREEN_WIDTH, 42) {};

    bool wasClicked() override;

    void loop() override;
    void onLongClicked() override;

    bool hitsLock(float lock);
};


#endif //PUI_PULLDOWNBAR_H
