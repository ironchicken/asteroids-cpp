#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <memory>
#include "Actor.hpp"
#include "Component.hpp"
#include "SDL_render.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(std::shared_ptr<Actor> owner, int drawOrder = 100) : Component(owner, drawOrder) { }
    ~SpriteComponent();
    virtual void draw(SDL_Renderer* renderer);
    virtual void setTexture(SDL_Texture* texture);

    int getDrawOrder() const { return drawOrder; }
    int getTextureWidth() const { return textureWidth; }
    int getTextureHeight() const { return textureHeight; }

protected:
    SDL_Texture* texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

#endif
