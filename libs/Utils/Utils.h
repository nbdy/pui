//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_UTILS_H
#define PUI_UTILS_H

#include <ctime>
#include <dirent.h>

#include <fplus.h>

// add other screen sizes here
#ifdef PINEPHONE
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440
#elif defined(GENERIC_FULLHD)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#endif

#define TIMESTAMP_FORMAT_LOG "%d.%m.%Y-%H:%M:%S"
#define TIMESTAMP_FORMAT_FILE "%d_%m_%Y-%H_%M_%S.log"

class Utils {
public:
    Utils();

    static std::vector<std::string> listDirectory(const std::string& path);
    static std::string getTimestamp(const std::string& format=TIMESTAMP_FORMAT_LOG);
};


#endif //PUI_UTILS_H
