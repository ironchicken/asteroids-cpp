#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <vector>
#include "Game.hpp"
#include "Vector2.hpp"

class Component;

class Actor {
public:
    enum class State {
        Active,
        Paused,
        Dead
    };

    Actor(const std::shared_ptr<Game> game);
    virtual ~Actor();

    void update(const float deltaTime);
    void updateComponents(const float deltaTime);
    virtual void updateActor(const float deltaTime);

    void addComponent(const std::shared_ptr<Component> component);
    void removeComponent(const std::shared_ptr<Component> component);

private:
    State state;
    Vector2 position;
    float scale;
    float rotation;
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<Game> game;
};

#endif
