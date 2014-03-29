#include "player.h"

Player::Player(const SDL_Point& point, const Sprite& sprite)
    : GameObject(point), m_sprite(sprite)
{
}

void Player::onRender(SDL_Renderer* ren, const Camera& cam) const
{
    m_sprite.onRender(ren, applyCamera(cam));
}
