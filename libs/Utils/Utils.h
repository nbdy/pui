//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_UTILS_H
#define PUI_UTILS_H

#include <ctime>
#include <cstring>
#include <dirent.h>

#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include <fplus.h>
#include <loguru/loguru.hpp>
#include <ricons.h>

#ifdef PINEPHONE
#define LOGURU_STACKTRACES 0
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440
#define FRAME_RATE 60
#elif defined(GENERIC_FULLHD)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FRAME_RATE 60
#else
#define SCREEN_WIDTH (float) 720 / 2
#define SCREEN_HEIGHT (float) 1440 / 2
#define FRAME_RATE 60
#endif

#ifdef DEBUG
#define LOG_DIRECTORY "./log/"
#define MODULE_DIRECTORY "./"
#else
#define LOG_DIRECTORY "/var/lib/pui/log/"
#define MODULE_DIRECTORY "/var/lib/pui/modules/"
#define ICON_DIRECTORY "/var/lib/pui/icons/"
#endif

#define TIMESTAMP_FORMAT_ADB "%a., %d. %b."
#define TIMESTAMP_FORMAT_HM "%H:%M"
#define TIMESTAMP_FORMAT_HMS "%H:%M:%S"
#define TIMESTAMP_FORMAT_LOG "%d.%m.%Y-%H:%M:%S"
#define TIMESTAMP_FORMAT_FILE "%d_%m_%Y-%H_%M_%S.log"

#define LED_PATH "/sys/class/leds/"
#define NETWORK_PATH "/sys/class/net/"
#define THERMAL_PATH "/sys/class/thermal/"
#define BACKLIGHT_PATH "/sys/class/backlight/backlight/"
#define POWER_SUPPLY_BATTERY_PATH "/sys/class/power_supply/axp20x-battery/"
#define POWER_SUPPLY_USB_PATH "/sys/class/power_supply/axp20x-usb/"

typedef std::vector<std::string> strVec;

class Utils {
protected:

public:
    Utils();

    static std::vector<std::string> listDirectory(const std::string& path);
    static std::string getTimestamp(const std::string& format=TIMESTAMP_FORMAT_LOG);
    static unsigned long getTimestampLong();
    static Texture2D getIcon(const std::string& iconName, Vector2 size);

    template<typename T> static T readValue(const std::string& path);

    template<typename T> static T readBatteryValue(const std::string& file);

    static int getBatteryCapacity();
    static int getBatteryConstantChargeCurrent();
    static int getBatteryVoltage();
    static int getBatteryCurrent();
    static std::string getBatteryHealth();
    static std::string getBatteryState();
    static bool isBatteryCharging();

    template<typename T> static T readBacklightValue(const std::string& file);
    static int getBacklightBrightness();
    static int getBacklightMaxBrightness();

    static strVec getThermalZones();
    template<typename T> static T readThermalValue(const std::string &thermal, const std::string& file);
    static int readThermalTempValue(const std::string& zone);
    static unsigned long getAverageTemperature();

    template<class T> static T readLEDValue(const std::string &led, const std::string& file);
    template<class T> static T readBlueLEDValue(const std::string& file);
    template<class T> static T readGreenLEDValue(const std::string& file);
    template<class T> static T readRedLEDValue(const std::string& file);
    template<class T> static T readWhiteLEDValue(const std::string& file);

    static strVec getNetworkInterfaces();
    template<typename T> static T readNetworkValue(const std::string& iface, const std::string& file);
    static std::string getNetworkInterfaceMAC(const std::string& iface);
    static int getNetworkInterfaceSpeed(const std::string& iface);
    static int getNetworkInterfaceRXSpeed(const std::string& iface);
    static int getNetworkInterfaceTXSpeed(const std::string& iface);

};


#endif //PUI_UTILS_H
