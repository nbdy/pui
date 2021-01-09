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

    doRun = true;
}

Manager::~Manager() {
    delete pulldownBar;
    moduleManager.unloadAllModules();
}

void Manager::run() {
    LOG_F(INFO, "Initializing SDL");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
        LOG_F(ERROR, "Error whilst initializing SDL: %s", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
#ifdef FULL_SCREEN
SDL_WINDOW_FULLSCREEN |
#endif
            SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

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
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    LOG_F(INFO, "Starting drawing loop.");
    while(doRun) {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                doRun = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                doRun = false;
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        ImGui::Begin("pui");
        ImGui::SetNextWindowPos(ImVec2 {0, 0});
        ImGui::SetWindowSize(ImVec2 {SCREEN_WIDTH, SCREEN_HEIGHT});
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    LOG_F(INFO, "Stopped drawing loop.");

    LOG_F(INFO, "Saving state.");
    saveState();

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

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
