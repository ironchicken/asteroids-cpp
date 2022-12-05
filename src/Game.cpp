#include <algorithm>
#include <memory>
#include "Actor.hpp"
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

void Game::addActor(const std::shared_ptr<Actor> actor) {
    if (updatingActors) {
        pendingActors.emplace_back(actor);
    } else {
        actors.emplace_back(actor);
    }
}

void Game::removeActor(const std::shared_ptr<Actor> actor) {
    pendingActors.erase(std::remove(pendingActors.begin(), pendingActors.end(), actor));
    actors.erase(std::remove(actors.begin(), actors.end(), actor));
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

    updatingActors = true;
    for (auto actor : actors) {
        actor->update(deltaTime);
    }
    updatingActors = false;

    for (auto pending : pendingActors) {
        actors.emplace_back(pending);
    }
    pendingActors.clear();

    auto dead = std::remove_if(
        actors.begin(),
        actors.end(),
        [](const std::shared_ptr<Actor> a) {
            return a->getState() == Actor::State::Dead;
        });
    actors.erase(dead);
}

void Game::generateOutput() { }
