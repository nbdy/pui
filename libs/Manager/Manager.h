//
// Created by nbdy on 21.12.20.
//

#ifndef PUI_MANAGER_H
#define PUI_MANAGER_H

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440
#define FRAME_RATE 60

#ifdef DEBUG
#define LOG_DIRECTORY "./log/"
#define MODULE_DIRECTORY "./"
#else
#define LOG_DIRECTORY "/var/pui/log/"
#define MODULE_DIRECTORY "/var/pui/modules/"
#endif

#include <raylib.h>

#include <fplus.h>
#include <args.h>
#include <loguru/loguru.hpp>

#include <ModuleManager/ModuleManager.h>

class Manager {
public:
    explicit Manager(int argc, char **argv);
    void parseConfiguration(const std::string& path);

    void run();
    void work();
    void saveState();
private:
    args::ArgumentParser parser;
    args::HelpFlag help;
    args::ValueFlag<std::string> configFile;
    args::ValueFlag<int> screenHeight;
    args::ValueFlag<int> screenWidth;
    args::ValueFlag<int> frameRate;
    args::ValueFlag<std::string> moduleDirectory;
    args::ValueFlag<std::string> logDirectory;

    ModuleManager *moduleManager;
};


#endif //PUI_MANAGER_H
