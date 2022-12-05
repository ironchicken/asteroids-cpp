#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "SDL2/SDL.h"

class Actor;

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
    void addActor(const std::shared_ptr<Actor> actor);
    void removeActor(const std::shared_ptr<Actor> actor);

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool isRunning;
    int frameRate;
    Uint32 ticksCount;
    bool updatingActors;
    std::vector<std::shared_ptr<Actor>> actors;
    std::vector<std::shared_ptr<Actor>> pendingActors;
};

#endif
