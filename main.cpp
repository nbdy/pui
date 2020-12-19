#include <raylib.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1440


void mainScreen() {

}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pui");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        mainScreen(); // todo state machine / switching views

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
