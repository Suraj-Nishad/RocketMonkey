#include "player.h"

Player::Player(b2World* b2world, const SDL_Point& point, const Sprite& sprite)
    : GameObject(b2world, point, b2_dynamicBody), m_sprite(sprite)
{
}

void Player::onRender(SDL_Renderer* ren, const Camera& cam) const
{
    m_sprite.onRender(ren, applyCamera(cam));
}

void Player::onLoop()
{
    b2Vec2 vel = getBody()->GetLinearVelocity();
    vel.x = 2;
    getBody()->SetLinearVelocity(vel);
}
