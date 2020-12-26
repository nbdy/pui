//
// Created by nbdy on 21.12.20.
//

#ifndef PUI_MANAGER_H
#define PUI_MANAGER_H

#include <fplus.h>
#include <args.h>
#include <loguru/loguru.hpp>

#include <ModuleManager/ModuleManager.h>

#define SYSTEM_BUTTON_PADDING 2
#define SYSTEM_BUTTON_HEIGHT 42
#define SYSTEM_BUTTON_WIDTH (float) (SCREEN_WIDTH - (float) SYSTEM_BUTTON_PADDING * 3) / 3

class Manager {
public:
    explicit Manager(int argc, char **argv);
    void parseConfiguration(const std::string& path);

    void run();
    void loop();
    void saveState();

    virtual void backButtonClicked();
    virtual void homeButtonClicked();
    virtual void otherButtonClicked();

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
};


#endif //PUI_MANAGER_H
