//
// Created by nbdy on 21.12.20.
//

#include "Manager.h"

#include <loguru/loguru.cpp>

Manager::Manager(int argc, char **argv):
parser(("pui - pinephone ui")),
help(parser, "help", "display this help text", {'h', "help"}),
configFile(parser, "string", "config file path", {'c', "config"}),
screenHeight(parser, "int", "screen height", {"sh", "screen-height"}, SCREEN_HEIGHT),
screenWidth(parser, "int", "screen width", {"sw", "screen-width"}, SCREEN_WIDTH),
frameRate(parser, "int", "frame rate", {"fr", "frame-rate"}, FRAME_RATE),
moduleDirectory(parser, "string", "dir where all the modules live", {"md", "module-directory"}, MODULE_DIRECTORY),
logDirectory(parser, "string", "dir where all the logs go", {"ld", "log-directory"}, LOG_DIRECTORY),
systemButtonGroup(HButtonGroup(Vector2 {(float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT - (float) SYSTEM_BUTTON_HEIGHT / 2},Vector2 {SCREEN_WIDTH, SYSTEM_BUTTON_HEIGHT},{
    Button(Utils::getIcon(RICON_ARROW_LEFT_FILL, ""), SYSTEM_BUTTON_SIZE, systemButtonBackCallback, this, SYSTEM_BUTTON_OUTLINE),
    Button(Utils::getIcon(RICON_HOUSE, ""), SYSTEM_BUTTON_SIZE, systemButtonHomeCallback, this, SYSTEM_BUTTON_OUTLINE),
    Button(Utils::getIcon(RICON_LAYERS, ""), SYSTEM_BUTTON_SIZE, systemButtonOtherCallback, this, SYSTEM_BUTTON_OUTLINE)
}, SYSTEM_BUTTON_PADDING))
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

    loguru::init(argc, argv);

    std::string logDir;
    if(!fplus::is_suffix_of(std::string("/"), logDirectory.Get())) logDir = logDirectory.Get() + "/" + Utils::getTimestamp(TIMESTAMP_FORMAT_FILE);
    else logDir = logDirectory.Get() + Utils::getTimestamp(TIMESTAMP_FORMAT_FILE);

    loguru::add_file(logDir.c_str(), loguru::Append, loguru::Verbosity_INFO);

    moduleManager = ModuleManager(moduleDirectory.Get());

    LOG_F(INFO, "Available modules in %s:", moduleManager.getModuleDirectory().c_str());
    for(const auto& m : moduleManager.getLoadableModules()) LOG_F(INFO, "\t%s", m.c_str());

    LOG_F(INFO, "Loading all modules.");
    moduleManager.loadAllModules();
}

void Manager::run() {
    LOG_F(INFO, "Initializing window with height '%i' and width '%i'.", screenHeight.Get(), screenWidth.Get());
    InitWindow(screenWidth.Get(), screenHeight.Get(), "pui");
    LOG_F(INFO, "Setting frame rate to '%i'.", frameRate.Get());
    SetTargetFPS(frameRate.Get());

    LOG_F(INFO, "Starting drawing loop.");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        work();

        EndDrawing();
    }
    LOG_F(INFO, "Stopped drawing loop.");

    LOG_F(INFO, "Saving state.");
    saveState();

    CloseWindow();

    LOG_F(INFO, "Unloading modules.");
    moduleManager.unloadAllModules();
}

// 3d ui? like a spinnable sphere with clickable boxes

// overview of all modules and where they are so they can be resized
void Manager::work() {
    systemButtonGroup.work();
    systemButtonGroup.draw();
}

void Manager::parseConfiguration(const std::string &path) {
    std::cout << "parsing configuration" << std::endl; // todo
}

void Manager::saveState() {
    // todo
}

void Manager::systemButtonBackCallback(void *ctx) {
    auto *mgr = (Manager*) ctx; // todo
    LOG_F(INFO, "systemButtonBackCallback");
}

void Manager::systemButtonHomeCallback(void *ctx) {
    auto *mgr = (Manager*) ctx; // todo
    LOG_F(INFO, "systemButtonHomeCallback");
}

void Manager::systemButtonOtherCallback(void *ctx) {
    auto *mgr = (Manager*) ctx; // todo
    LOG_F(INFO, "systemButtonOtherCallback");
}
