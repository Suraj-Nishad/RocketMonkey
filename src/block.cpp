#include "block.h"
#include "wall.h"

Block::Block(const Wall& wall, SDL_Point pos, bool filled)
    : GameObject(pos), m_filled(filled), m_wall(wall)
{
}

void Block::onRender(SDL_Renderer* ren)
{
    if(m_filled) {
        const Camera& cam = m_wall.getCamera();
        SDL_Point pt = m_pos;
        SDL_Rect region = cam.getViewableRegion();
        pt.x -= region.x;
        pt.y -= region.y;
        m_wall.getSprites().getSprite("red").onRender(ren, pt);
    }
}
