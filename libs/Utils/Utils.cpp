//
// Created by nbdy on 20.12.20.
//

#include "Utils.h"

#include <loguru/loguru.cpp>

Utils::Utils() = default;

std::vector<std::string> Utils::listDirectory(const std::string &path) {
    std::string delim = (!fplus::is_suffix_of(std::string("/"), path) ? "/" : "");
    std::vector<std::string> r;
    DIR *d;
    struct dirent *e;
    if((d = opendir(path.c_str())) != nullptr) {
        while((e = readdir(d)) != nullptr) r.emplace_back(path + delim + e->d_name);
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

unsigned long Utils::getTimestampLong() {
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    return 1000000000 * t.tv_sec + t.tv_nsec;
}

Texture2D Utils::getIcon(const std::string &iconName, Vector2 size) {
    std::string iconPath = std::string(ICON_DIRECTORY) + iconName + ".png";
    if(FileExists(iconPath.c_str())) {
        auto icon = LoadImage(iconPath.c_str());
        ImageResize(&icon, size.x, size.y);
        auto r = LoadTextureFromImage(icon);
        UnloadImage(icon);
        return r;
    }
    return Texture2D {};
}

strVec Utils::getNetworkInterfaces() {
    return listDirectory(NETWORK_PATH);
}

std::string Utils::getNetworkInterfaceMAC(const std::string &iface) {
    return readNetworkValue<std::string>(iface, "address");
}

int Utils::getNetworkInterfaceSpeed(const std::string &iface) {
    return readNetworkValue<int>(iface, "speed");
}

int Utils::getNetworkInterfaceRXSpeed(const std::string &iface) {
    return readNetworkValue<int>(iface, "statistics/rx_packets");
}

int Utils::getNetworkInterfaceTXSpeed(const std::string &iface) {
    return readNetworkValue<int>(iface, "statistics/tx_packets");
}

template<typename T>
T Utils::readNetworkValue(const std::string &iface, const std::string &file) {
    return fplus::read_value_unsafe<T>(fplus::read_text_file(NETWORK_PATH + iface +  + "/" + file)());
}


