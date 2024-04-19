#include "Engine.h"

#define M_PI 3.14

int main() {
    Engine game(800, 600, "Simple Game Engine");
    game.setFullscreen(false);
    game.setResolution(800, 600);
    game.setFrameRate(60);
    game.setPredefinedBackgroundColor(1);

    game.run();

    return 0;
}
