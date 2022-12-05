#ifndef GAME_H
#define GAME_H

#include <memory>
#include "SDL2/SDL.h"

class Game {
public:
    Game() {};
    bool initialize();
    void shutDown();
    void run();

private:
    void processInput();
    void update();
    void generateOutput();

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool isRunning;
    int frameRate;
    Uint32 ticksCount;
};

#endif
