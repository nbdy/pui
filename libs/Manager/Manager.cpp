//
// Created by nbdy on 21.12.20.
//

#include "Manager.h"

#include <utility>

Manager::Manager(int argc, char **argv):
parser(("pui - pinephone ui")),
help(parser, "help", "display this help text", {'h', "help"}),
configFile(parser, "string", "config file path", {'c', "config"}),
screenHeight(parser, "int", "screen height", {"sh", "screen-height"}, SCREEN_HEIGHT),
screenWidth(parser, "int", "screen width", {"sw", "screen-width"}, SCREEN_WIDTH),
frameRate(parser, "int", "frame rate", {"fr", "frame-rate"}, FRAME_RATE),
moduleDirectory(parser, "string", "dir where all the modules live", {"md", "module-directory"}, MODULE_DIRECTORY),
logDirectory(parser, "string", "dir where all the logs go", {"ld", "log-directory"}, LOG_DIRECTORY)
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
}

Manager::~Manager() {
    delete pulldownBar;
    moduleManager.unloadAllModules();
}

void Manager::run() {
    LOG_F(INFO, "Initializing window with height '%i' and width '%i'.", screenHeight.Get(), screenWidth.Get());
    InitWindow(screenWidth.Get(), screenHeight.Get(), "pui");
    LOG_F(INFO, "Setting frame rate to '%i'.", frameRate.Get());
    SetTargetFPS(frameRate.Get());

    moduleManager = ModuleManager(moduleDirectory.Get());

    LOG_F(INFO, "Available modules in %s:", moduleManager.getModuleDirectory().c_str());
    for(const auto& m : moduleManager.getLoadableModules()) LOG_F(INFO, "\t%s", m.c_str());

    LOG_F(INFO, "Loading all modules.");
    moduleManager.loadAllModules();

    modVec gridModules;

    for(auto m : moduleManager.getLoadedModules()) {
        LOG_F(INFO, "%s, %s : %s", m->getName().c_str(), m->getVersion().c_str(), m->getDescription().c_str());
        if(m->getType() == UI) gridModules.emplace_back(m);
    }

    pulldownBar = new PulldownBar(moduleManager.getLoadedModules());

    allModules = GridView<Manager>(
            Rectangle {0, pulldownBar->getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT - SYSTEM_BUTTON_HEIGHT}, gridModules);

    LOG_F(INFO, "Starting drawing loop.");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        loop();

        EndDrawing();
    }
    LOG_F(INFO, "Stopped drawing loop.");

    LOG_F(INFO, "Saving state.");
    saveState();

    CloseWindow();

    LOG_F(INFO, "Unloading modules.");
    moduleManager.unloadAllModules();
}

void Manager::work() {
    auto ctx = moduleManager.accumulateContext();
    for(auto& m : moduleManager.getLoadedModules()) taskflow.emplace([this, ctx, m](){m->work(this, ctx);});
    executor.run(taskflow).wait();
    taskflow.clear();
}

void Manager::loop() {
    auto cm = getCurrentModule();
    if(cm != nullptr) cm->loop(this);
    else allModules.loop(this);

    if(GuiButton(Rectangle {0, SCREEN_HEIGHT - SYSTEM_BUTTON_HEIGHT, SYSTEM_BUTTON_WIDTH, SYSTEM_BUTTON_HEIGHT},
                 GuiIconText(RICON_ARROW_LEFT_FILL, nullptr))) backButtonClicked();
    if(GuiButton(Rectangle {SCREEN_WIDTH / 2 - SYSTEM_BUTTON_WIDTH / 2, SCREEN_HEIGHT - SYSTEM_BUTTON_HEIGHT, SYSTEM_BUTTON_WIDTH, SYSTEM_BUTTON_HEIGHT},
                 GuiIconText(RICON_HOUSE, nullptr))) homeButtonClicked();
    if(GuiButton(Rectangle {SCREEN_WIDTH - SYSTEM_BUTTON_WIDTH, SCREEN_HEIGHT - SYSTEM_BUTTON_HEIGHT, SYSTEM_BUTTON_WIDTH, SYSTEM_BUTTON_HEIGHT},
                 GuiIconText(RICON_LAYERS, nullptr))) otherButtonClicked();

    pulldownBar->loop();
}

void Manager::parseConfiguration(const std::string &path) {
    std::cout << "parsing configuration" << std::endl; // todo
}

void Manager::saveState() {
    // todo
}

void Manager::backButtonClicked() {
    auto cm = getCurrentModule();
    if(cm != nullptr) cm->backButtonClicked(this);
}

void Manager::homeButtonClicked() {
    setCurrentModule(nullptr);
}

void Manager::otherButtonClicked() {
    LOG_F(INFO, "otherButtonClicked");
}

void Manager::setCurrentModule(ptModule module) {
    currentModule = module;
}

ptModule Manager::getCurrentModule() {
    return currentModule;
}

ModuleManager *Manager::getModuleManager() {
    return &moduleManager;
}
