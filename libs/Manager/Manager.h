//
// Created by nbdy on 21.12.20.
//

#ifndef PUI_MANAGER_H
#define PUI_MANAGER_H

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440
#define FRAME_RATE 60

#include <raylib.h>

#include <fplus.h>

#include <ModuleManager/ModuleManager.h>

class Manager {
public:
    explicit Manager(char **argv);

    void parseArguments(char **argv);
    void parseConfiguration(const std::string& path);

    void run();
    void work();

    static void printHelp();

protected:
    static std::string getNextArgOrExit(char** argv, int currentIndex);

private:
    std::string configPath;

    int screenHeight = SCREEN_HEIGHT;
    int screenWidth = SCREEN_WIDTH;
    int frameRate = FRAME_RATE;
};


#endif //PUI_MANAGER_H
