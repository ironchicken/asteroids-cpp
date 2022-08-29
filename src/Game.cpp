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

    return true;
}
