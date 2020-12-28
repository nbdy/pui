//
// Created by nbdy on 20.12.20.
//

#include "Utils.h"

Utils::Utils() = default;

std::vector<std::string> Utils::listDirectory(const std::string &path) {
    std::vector<std::string> r;
    DIR *d;
    struct dirent *e;
    if((d = opendir(path.c_str())) != nullptr) {
        while((e = readdir(d)) != nullptr) r.emplace_back(e->d_name);
        closedir(d);
    }
    return r;
}

std::string Utils::getTimestamp(const std::string &format) {
    time_t tp = time(nullptr);
    char b[256];
    struct tm t = *localtime(&tp);
    strftime(b, sizeof(b), format.c_str(), &t);
    return b;
}
