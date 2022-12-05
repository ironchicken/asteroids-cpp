#include "Component.hpp"

Component::Component(std::shared_ptr<Actor> owner, int updateOrder) {
    this->owner = owner;
    this->updateOrder = updateOrder;
}

Component::~Component() { }

void Component::update(const float deltaTime) { }
