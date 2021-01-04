//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_UTILS_H
#define PUI_UTILS_H

#include <time.h>
#include <cstring>
#include <dirent.h>

#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include <fplus.h>
#include <loguru/loguru.hpp>
#include <ricons.h>

#ifdef PINEPHONE
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
#define LOG_DIRECTORY "/var/pui/log/"
#define MODULE_DIRECTORY "/var/pui/modules/"
#define ICON_DIRECTORY "/var/pui/icons/"
#endif

#define TIMESTAMP_FORMAT_HM "%H:%M"
#define TIMESTAMP_FORMAT_HMS "%H:%M:%S"
#define TIMESTAMP_FORMAT_LOG "%d.%m.%Y-%H:%M:%S"
#define TIMESTAMP_FORMAT_FILE "%d_%m_%Y-%H_%M_%S.log"

#define NETWORK_PATH "/sys/class/net/eth0/address/"

typedef std::vector<std::string> strVec;

class Utils {
protected:

public:
    Utils();

    static std::vector<std::string> listDirectory(const std::string& path);
    static std::string getTimestamp(const std::string& format=TIMESTAMP_FORMAT_LOG);
    static unsigned long getTimestampLong();
    static Texture2D getIcon(const std::string& iconName, Vector2 size);

    int getBatteryCapacity();

    void setScreenBrightness(int value);
    int getScreenBrightness();

    static strVec getNetworkInterfaces();
    template<typename T> static T readNetworkValue(const std::string& iface, const std::string& file);
    static std::string getNetworkInterfaceMAC(const std::string& iface);
    static int getNetworkInterfaceSpeed(const std::string& iface);
    static int getNetworkInterfaceRXSpeed(const std::string& iface);
    static int getNetworkInterfaceTXSpeed(const std::string& iface);

};


#endif //PUI_UTILS_H
