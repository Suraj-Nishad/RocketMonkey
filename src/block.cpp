#include "block.h"
#include "wall.h"

Block::Block(const Wall& wall, SDL_Point pos, bool filled)
    : GameObject(pos), m_filled(filled), m_wall(wall)
{
}

void Block::onRender(SDL_Renderer* ren, const Camera& cam) const
{
    if(m_filled) {
        m_wall.getSprites().getSprite("red").onRender(ren, applyCamera(cam));
    }
}
