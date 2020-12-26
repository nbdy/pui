//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_UTILS_H
#define PUI_UTILS_H

#include <ctime>
#include <cstring>
#include <dirent.h>

#define RAYGUI_SUPPORT_ICONS
#include <ricons.h>

#include <fplus.h>

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
#endif

#define TIMESTAMP_FORMAT_LOG "%d.%m.%Y-%H:%M:%S"
#define TIMESTAMP_FORMAT_FILE "%d_%m_%Y-%H_%M_%S.log"

class Utils {
protected:

public:
    Utils();

    static std::vector<std::string> listDirectory(const std::string& path);
    static std::string getTimestamp(const std::string& format=TIMESTAMP_FORMAT_LOG);

    static const char* getIcon(guiIconName icon, const char* text);
};


#endif //PUI_UTILS_H
