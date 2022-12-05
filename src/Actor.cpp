#include <algorithm>
#include "Actor.hpp"
#include "Vector2.hpp"

Actor::Actor(const std::shared_ptr<Game> game) {
    this->game = game;
    state = State::Active;
    position = Vector2 { 0.0, 0.0 };
    scale = 1.0;
    rotation = 0.0;
}

Actor::~Actor() { }

void Actor::update(const float deltaTime) { }

void Actor::updateComponents(const float deltaTime) { }

void Actor::updateActor(const float deltaTime) { }

void Actor::addComponent(const std::shared_ptr<Component> component) {
    components.push_back(component);
}

void Actor::removeComponent(const std::shared_ptr<Component> component) {
    auto removed = std::remove_if(
        components.begin(),
        components.end(),
        [&](const std::shared_ptr<Component> c) {
            return c == component;
        });
    components.erase(removed);
}
