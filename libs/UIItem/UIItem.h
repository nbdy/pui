//
// Created by nbdy on 03.01.21.
//

#ifndef PUI_UIITEM_H
#define PUI_UIITEM_H

#include <Utils/Utils.h>

class UIItem {
protected:
    float height = 1;
    float width = 1;
    float x = 0;
    float y = 0;

    unsigned long firstClicked = 0;
    unsigned long clicked = 0;

    unsigned long longClickThreshold = 840000000;

public:
    UIItem();
    UIItem(float x, float y, float height, float width);
    UIItem(float x, float y, float height, float width, long longClickThreshold);
    ~UIItem();

    virtual void loop();
    [[nodiscard]] virtual bool wasClicked();
    [[nodiscard]] bool wasLongClicked() const;

    virtual void onClicked() {LOG_F(WARNING, "UIItem::onClicked should be overwritten");};
    virtual void onLongClicked() {LOG_F(WARNING, "UIItem::onLongClicked should be overwritten");};
};


#endif //PUI_UIITEM_H
