#include <Manager/Manager.h>

int main([[maybe_unused]] int argc, char** argv) {
    Manager mgr(argv);
    mgr.run();
    return 0;
}
