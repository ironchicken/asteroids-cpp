#include <cmath>
#include "SpriteComponent.hpp"
#include "SDL_render.h"

SpriteComponent::~SpriteComponent() { }

void SpriteComponent::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_Rect rect;
        rect.w = textureWidth * owner->getScale();
        rect.h = textureHeight * owner->getScale();
        rect.x = owner->getPosition().getX() - rect.w / 2;
        rect.y = owner->getPosition().getY() - rect.h / 2;

        SDL_RenderCopyEx(
            renderer,
            texture,
            nullptr,
            &rect,
            owner->getRotation() * (180 / M_PI),
            nullptr,
            SDL_FLIP_NONE);
    }
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
    this->texture = texture;

    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}
