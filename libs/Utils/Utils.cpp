//
// Created by nbdy on 20.12.20.
//

#include "Utils.h"

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

Utils::Utils() = default;

