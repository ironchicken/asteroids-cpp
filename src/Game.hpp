#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "SDL2/SDL.h"

class Actor;
class SpriteComponent;

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
    void addSprite(const std::shared_ptr<SpriteComponent> sprite);
    SDL_Texture* loadTexture(const std::string& fileName);
    SDL_Texture* getTexture(const std::string& fileName);

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
    std::vector<std::shared_ptr<SpriteComponent>> sprites;
    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif
