//
// Created by nbdy on 21.12.20.
//

#ifndef PUI_MANAGER_H
#define PUI_MANAGER_H

#include <raylib.h>

#include <fplus.h>
#include <args.h>
#include <loguru/loguru.hpp>

#include <ButtonGroup/ButtonGroup.h>
#include <ModuleManager/ModuleManager.h>

#define SYSTEM_BUTTON_OUTLINE 2
#define SYSTEM_BUTTON_PADDING 4
#define SYSTEM_BUTTON_HEIGHT 42
#define SYSTEM_BUTTON_WIDTH (float) (SCREEN_WIDTH - (float) SYSTEM_BUTTON_PADDING * 3) / 3
#define SYSTEM_BUTTON_SIZE Vector2 {SYSTEM_BUTTON_WIDTH, SYSTEM_BUTTON_HEIGHT}

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

    ModuleManager moduleManager;

    HButtonGroup systemButtonGroup;

    static void systemButtonBackCallback(void* ctx);
    static void systemButtonHomeCallback(void* ctx);
    static void systemButtonOtherCallback(void* ctx);
};


#endif //PUI_MANAGER_H
