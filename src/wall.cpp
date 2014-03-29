#include "wall.h"
#include <stdlib.h>
#include <algorithm>

static bool remove_old_blocks(const std::vector<Block*>& blocks)
{
    const Block* block = blocks.front();
    const int pixels_x = 100;
    if(block) {
        SDL_Point pos = block->getPos();
        const Camera& cam = block->getWall().getCamera();
        SDL_Rect region = cam.getViewableRegion();
        bool invisible = pos.x < region.x - pixels_x;
        if(invisible) {
            for(auto y = blocks.begin(); y != blocks.end(); y++) {
                delete *y;
            }
        }
        return invisible;
    }
    return true;
}


Wall::Wall(b2World* b2world, const SDL_Rect& screen, const SpriteFile& wall,
           const Camera& camera)
    : m_wall(wall), m_tunnel_size(3), m_screen(screen), m_camera(camera),
      m_b2world(b2world)
{
    const Sprite& normal = m_wall.getSprite("red");
    m_tiles.y = m_screen.h / normal.getHeight() + 2;
    m_tiles.x = m_screen.w / normal.getWidth() + 2;
    m_path.y = m_tiles.y / 2;
    m_path.x = 0;
    updateRegion();
}

void Wall::updateRegion()
{
    const SDL_Rect& region = m_camera.getViewableRegion();
    const Sprite& normal = m_wall.getSprite("red");
    const int x_start = region.x / normal.getWidth();
    const int x_end = x_start + m_tiles.x;
    for(int x = x_start; x < x_end; x++) {
        if(x >= m_path.x) {
            std::vector<Block*> blocks;
            /* draws one screen above, the current screen, and one below. */
            const int screen_heights = 3;
            const int y_start = region.y / normal.getHeight() - m_tiles.y;
            const int y_end = y_start + screen_heights * m_tiles.y;
            for(int y = y_start; y < y_end; y++) {
                bool filled = abs(y - m_path.y) > m_tunnel_size ? true : false;
                if(filled) {
                    SDL_Point pos;
                    pos.x = x * normal.getWidth();
                    pos.y = y * normal.getWidth();
                    blocks.push_back(new Block(m_b2world, *this, pos, filled));
                }
            }
            m_blocks.push_back(blocks);
            m_path.y += rand() % 2 ? 1 : -1;
            m_path.x++;
        }
    }
    m_blocks.erase(std::remove_if(m_blocks.begin(), m_blocks.end(),
                                  remove_old_blocks), m_blocks.end());
}

void Wall::onRender(SDL_Renderer* ren)
{
    for(auto x = m_blocks.begin(); x != m_blocks.end(); x++) {
        for(auto y = x->begin(); y != x->end(); y++) {
            (*y)->onRender(ren, m_camera);
        }
    }
}
