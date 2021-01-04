//
// Created by nbdy on 03.01.21.
//

#ifndef PUI_PULLDOWNBAR_H
#define PUI_PULLDOWNBAR_H

#include <BaseModule/BaseModule.h>
#include <UIItem/UIItem.h>

#include <utility>

class PulldownBar : public UIItem {
protected:
    modVec modules;

    std::string clockTextFormat = TIMESTAMP_FORMAT_HMS;
    float clockTextSize = 16;

    float brightnessSliderYOffset = 36;
    Texture2D texBrightnessLow;
    Texture2D texBrightnessHigh;
    float brightnessSliderValue = 60;

    float drawbackSpeed = 16;
    float lineThickness = 2;
    float firstYLock = SCREEN_HEIGHT / 4;
    float secondYLock = SCREEN_HEIGHT / 1.2;

    void drawPullbar();
    void drawBrightnessSlider();
    void drawClock(float x, float y) const;
    void drawDate(float x, float y);
    // todo:
    // void drawBattery();
    // void drawGSMSignal();
    // void drawWiFiSignal();
    // void drawNotifications();
    // void drawNetworkSpeed();
    // void drawMode() // flight / vibration / normal


    void loadTextures();

public:
    PulldownBar();
    explicit PulldownBar(modVec modules);

    bool wasClicked() override;

    void loop() override;
    void onLongClicked() override;
    void onClicked() override;

    bool hitsLock(float lock);
};


#endif //PUI_PULLDOWNBAR_H
