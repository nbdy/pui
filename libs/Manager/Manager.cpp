//
// Created by nbdy on 21.12.20.
//

#include "Manager.h"

Manager::Manager(int argc, char **argv):
parser(("pui - pinephone ui")),
help(parser, "help", "display this help text", {'h', "help"}),
configFile(parser, "string", "config file path", {'c', "config"}),
screenHeight(parser, "int", "screen height", {"sh", "screen-height"}, SCREEN_HEIGHT),
screenWidth(parser, "int", "screen width", {"sw", "screen-width"}, SCREEN_WIDTH),
frameRate(parser, "int", "frame rate", {"fr", "frame-rate"}, FRAME_RATE),
moduleDirectory(parser, "string", "dir where all the modules live", {"md", "module-directory"}, MODULE_DIRECTORY)
{
    try {
        parser.ParseCLI(argc, argv);
    } catch(args::Help&) {
        std::cout << parser << std::endl;
        exit(0);
    } catch(args::ParseError& e){
        std::cerr << e.what() << std::endl;
        std::cerr << parser << std::endl;
        exit(0);
    } catch(args::ValidationError& e){
        std::cerr << e.what() << std::endl;
        std::cerr << parser << std::endl;
        exit(0);
    }

    if(!configFile.Get().empty()) parseConfiguration(configFile.Get());

    moduleManager = new ModuleManager(moduleDirectory.Get());
    moduleManager->loadAllModules();
}

void Manager::run() {
    InitWindow(screenWidth.Get(), screenHeight.Get(), "pui");
    SetTargetFPS(frameRate.Get());

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        work();

        EndDrawing();
    }

    saveState();

    CloseWindow();

    moduleManager->unloadAllModules();
}

void Manager::work() {
    moduleManager->work(moduleManager->accumulateContext());
    moduleManager->drawModules();
}

void Manager::parseConfiguration(const std::string &path) {
    std::cout << "parsing configuration" << std::endl; // todo
}

void Manager::saveState() {
    // todo
}
