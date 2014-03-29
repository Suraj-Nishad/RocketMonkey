#include "block.h"
#include "wall.h"

Block::Block(b2World* b2world, const Wall& wall, SDL_Point pos, bool filled)
    : GameObject(b2world, pos, b2_staticBody), m_filled(filled), m_wall(wall)
{
}

void Block::onRender(SDL_Renderer* ren, const Camera& cam) const
{
    if(m_filled) {
        m_wall.getSprites().getSprite("red").onRender(ren, applyCamera(cam));
    }
}
