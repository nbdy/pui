//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_UTILS_H
#define PUI_UTILS_H

#include <dirent.h>

#include <vector>
#include <string>
#include <functional>

class Utils {
public:
    Utils();

    static std::vector<std::string> listDirectory(const std::string& path);
};


#endif //PUI_UTILS_H
