#include "Game.hpp"

bool Game::initialize() {
    auto initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        SDL_Log("Failed to initialise SDL: %s", SDL_GetError());
        return false;
    }

    width = 1024;
    height = 768;
    window = SDL_CreateWindow("Asteroids", 100, 100, width, height, 0);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    frameRate = 32;
    ticksCount = 0;

    return true;
}

void Game::shutDown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    while (isRunning) {
        processInput();
        update();
        generateOutput();
    }
}

void Game::processInput() { }

void Game::update() {
    auto ticks = SDL_GetTicks();
    if (ticks - ticksCount < frameRate) {
        SDL_Delay(ticks - ticksCount);
    }

    ticks = SDL_GetTicks();

    float deltaTime = (ticks - ticksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    ticksCount = ticks;

    if (!isRunning) {
        return;
    }
}

void Game::generateOutput() { }
