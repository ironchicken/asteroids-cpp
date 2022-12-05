#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Actor.hpp"

class Component {
public:
    Component(std::shared_ptr<Actor> owner, int updateOrder = 100);
    virtual ~Component();
    virtual void update(const float deltaTime);
    int getUpdateOrder() const { return updateOrder; }
protected:
    std::shared_ptr<Actor> owner;
    int updateOrder;
};

#endif
