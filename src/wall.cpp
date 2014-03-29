#include "wall.h"
#include <stdlib.h>     /* srand, rand */

Wall::Wall(const SDL_Rect& screen, const SpriteFile& wall, const Camera& camera)
    : m_wall(wall), m_tunnel_size(2), m_screen(screen), m_camera(camera)
{
    const Sprite& normal = m_wall.getSprite("red");
    m_tiles.y = m_screen.h / normal.getHeight() + 2;
    m_tiles.x = m_screen.w / normal.getWidth() + 2;
    m_path = m_tiles.y / 2;
    for(int x = 0; x < m_tiles.x; x++) {
        std::vector<Block*> blocks;
        for(int y = 0; y < m_tiles.y; y++) {
            bool filled = abs(y - m_path) > m_tunnel_size ? true : false;
            SDL_Point pos;
            pos.x = x * normal.getWidth();
            pos.y = y * normal.getWidth();
            blocks.push_back(new Block(*this, pos, filled));
        }
        m_blocks.push_back(blocks);
        m_path += rand() % 2 ? 1 : -1;
    }
}


void Wall::updateRegion()
{
    /* TODO: prune/populate block segments */
}

void Wall::onRender(SDL_Renderer* ren)
{
    for(auto x = m_blocks.begin(); x != m_blocks.end(); x++) {
        for(auto y = x->begin(); y != x->end(); y++) {
            (*y)->onRender(ren);
        }
    }
}
