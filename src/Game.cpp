#include <algorithm>
#include <memory>
#include "Actor.hpp"
#include "Game.hpp"
#include "SDL_image.h"

bool Game::initialize() {
    auto initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        SDL_Log("Failed to initialise SDL: %s", SDL_GetError());
        return false;
    }

    IMG_Init(IMG_INIT_PNG);

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
    IMG_Quit();
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

SDL_Texture* Game::loadTexture(const std::string& fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
        return nullptr;
    }

    return texture;
}

SDL_Texture* Game::getTexture(const std::string& fileName) {
    auto textureIt = textures.find(fileName);
    if (textureIt != textures.end()) {
        return (*textureIt).second;
    }

    auto texture = loadTexture(fileName);
    if (texture != nullptr) {
        textures.insert({ fileName, texture });
    }

    return texture;
}
