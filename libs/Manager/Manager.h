//
// Created by nbdy on 21.12.20.
//

#ifndef PUI_MANAGER_H
#define PUI_MANAGER_H

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440
#define FRAME_RATE 60
#define MODULE_DIRECTORY "/var/pui/modules/"

#include <raylib.h>

#include <fplus.h>
#include <args.h>

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

    ModuleManager *moduleManager;
};


#endif //PUI_MANAGER_H
