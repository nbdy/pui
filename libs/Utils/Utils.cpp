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
    return readValue<T>(NETWORK_PATH + iface +  + "/" + file);
}

int Utils::getBatteryCapacity() {
#ifdef PINEPHONE
    return readBatteryValue<int>("capacity");
#else
    return 100;
#endif

}

template<typename T>
T Utils::readValue(const std::string &path) {
    return fplus::read_value_unsafe<T>(fplus::read_text_file(path)());
}

template<typename T>
T Utils::readBatteryValue(const std::string &file) {
#ifdef PINEPHONE
    return readValue<T>(POWER_SUPPLY_BATTERY_PATH + file);
#else
    return T();
#endif

}

int Utils::getBatteryConstantChargeCurrent() {
    return readBatteryValue<int>("constant_charge_current");
}

int Utils::getBatteryVoltage() {
    return readBatteryValue<int>("voltage_now");
}

std::string Utils::getBatteryHealth() {
    return readBatteryValue<std::string>("health");
}

int Utils::getBatteryCurrent() {
    return readBatteryValue<int>("current_now");
}

template<typename T>
T Utils::readBacklightValue(const std::string &file) {
    return readValue<T>(BACKLIGHT_PATH + file);
}

int Utils::getBacklightBrightness() {
    return readBacklightValue<int>("brightness");
}

int Utils::getBacklightMaxBrightness() {
    return readBacklightValue<int>("max_brightness");
}

template<class T>
T Utils::readLEDValue(const std::string &led, const std::string& file) {
    return readValue<T>(LED_PATH + led + "/" + file);
}

template<class T>
T Utils::readBlueLEDValue(const std::string &file) {
    return readLEDValue<T>("blue:indicator", file);
}

template<class T>
T Utils::readGreenLEDValue(const std::string &file) {
    return readLEDValue<T>("green:indicator", file);
}

template<class T>
T Utils::readRedLEDValue(const std::string &file) {
    return readLEDValue<T>("red:indicator", file);
}

template<class T>
T Utils::readWhiteLEDValue(const std::string &file) {
    return readLEDValue<T>("white:flash", file);
}

template<typename T>
T Utils::readThermalValue(const std::string &thermal, const std::string& file) {
    return readValue<T>(THERMAL_PATH + thermal + "/" + file);
}

int Utils::readThermalTempValue(const std::string &zone) {
    return readThermalValue<int>("thermal_zone" + zone, "temp");
}

strVec Utils::getThermalZones() {
    return fplus::keep_if([](const std::string& v){return fplus::is_prefix_of(std::string("thermal_zone"), v);}, listDirectory(THERMAL_PATH));
}

unsigned long Utils::getAverageTemperature() {
    auto tz = getThermalZones();
    unsigned long r = 0;
    for(const auto& t : tz) r += readThermalTempValue(t);
    return r / tz.size();
}

std::string Utils::getBatteryState() {
#ifdef PINEPHONE
    return readBatteryValue<std::string>("status");
#else
    return "";
#endif
}

bool Utils::isBatteryCharging() {
    return "Charging" == getBatteryState();
}




