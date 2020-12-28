#include <Manager/Manager.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main(int argc, char** argv) {
    Manager mgr(argc, argv);
    mgr.run();
    return 0;
}
