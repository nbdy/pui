//
// Created by nbdy on 21.12.20.
//

#include "Manager.h"

Manager::Manager(char **argv) {
    parseArguments(argv);
}

void Manager::parseArguments(char **argv) {
    for(int i = 0; i < sizeof(argv); i++) {
        std::string a(argv[i]);
        if(fplus::is_elem_of(a, std::vector<std::string>{"-h", "--help"})) printHelp();
        else if(fplus::is_elem_of(a, std::vector<std::string>{"-c", "--config"})) parseConfiguration(getNextArgOrExit(argv, i));
        else if(fplus::is_elem_of(a, std::vector<std::string>{"-sh", "--screen-height"})) screenHeight = fplus::read_value_with_default<int>(getNextArgOrExit(argv, i), SCREEN_HEIGHT);
        else if(fplus::is_elem_of(a, std::vector<std::string>{"-sw", "--screen-width"})) screenWidth = fplus::read_value<int>(getNextArgOrExit(argv, i));
        else if(fplus::is_elem_of(a, std::vector<std::string>{"-fr", "--frame-rate"})) frameRate = fplus::read_value<int>(getNextArgOrExit(argv, i));
        // todo theme
    }
}

void Manager::printHelp() {
    std::cout << "usage: ./pui {arguments}" << std::endl;
    std::cout << "\t{argument}\t\t{description}" << std::endl;
    std::cout << "\t-h\t--help\tthis help text" << std::endl;
    std::cout << "\t-c\t--config\tparse this config file" << std::endl;
    std::cout << "\t-sh\t--screen-height\tdefault: 1440" << std::endl;
    std::cout << "\t-sw\t--screen-width\tdefault: 720" << std::endl;
    std::cout << "\t-fr\t--frame-rate\tdefault: 60" << std::endl;
    exit(0);
}

void Manager::run() {
    InitWindow(screenWidth, screenHeight, "pui");
    SetTargetFPS(frameRate);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        work(); // todo state machine / switching views

        EndDrawing();
    }

    CloseWindow();
}

void Manager::work() {

}

void Manager::parseConfiguration(const std::string &path) {
    // todo
}

std::string Manager::getNextArgOrExit(char **argv, int currentIndex) {
    if(sizeof(argv) <= currentIndex) printHelp();
    return argv[currentIndex + 1];
}
