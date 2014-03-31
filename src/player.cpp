#include "player.h"
#include <iostream>

Player::Player(b2World* b2world, const SDL_Point& point, const Sprite& sprite)
    : GameObject(b2world, &sprite, point, b2_dynamicBody), m_contact(false)
{
}

void Player::onLoop()
{
    b2Vec2 vel = getBody()->GetLinearVelocity();
    if(!m_contact) {
        vel.x = 2;
    }
    getBody()->SetLinearVelocity(vel);
}

void Player::startContact(GameObject*)
{
    m_contact = true;
}

void Player::endContact(GameObject*)
{
    m_contact = false;
}
