#include "wall.h"
#include <stdlib.h>
#include <algorithm>

enum WALL_ENUM {
    W_NONE = 0,
    W_TOP = 1 << 0,
    W_BOTTOM = 1 << 1,
    W_LEFT = 1 << 2,
    W_RIGHT = 1 << 3,
};

typedef struct {
    long operator()(const std::pair<int, int>& k) const {
        std::hash<int> hasher;
        return hasher(k.first);
    }
} PairKeyHash;


Wall::Wall(b2World* b2world, SDL_Renderer* ren, const SDL_Rect& screen,
           const Camera& camera)
    : m_wall(*new SpriteFile(ren, "img/wall.json")), m_tunnel_size(6),
      m_screen(screen), m_camera(camera),
      m_b2world(b2world)
{
    const Sprite& normal = m_wall.getSprite("0side");
    m_tiles.y = m_screen.h / normal.getHeight() + 2;
    m_tiles.x = m_screen.w / normal.getWidth() + 2;
    m_path.y = m_tiles.y / 2;
    m_path.x = 0;
    updateRegion();
}

void Wall::setWallTexture(Block& block, uint32_t wall_sides)
{
    int angle = 0;
    const Sprite* sprite = NULL;
    switch(wall_sides) {
        case W_NONE:
            angle = 0;
            sprite = &m_wall.getSprite("0side");
            break;
        case W_TOP:
            angle = 0;
            sprite = &m_wall.getSprite("1side");
            break;
        case W_BOTTOM:
            angle = 180;
            sprite = &m_wall.getSprite("1side");
            break;
        case W_TOP | W_BOTTOM:
            angle = 90;
            sprite = &m_wall.getSprite("2side_opp");
            break;
        case W_LEFT:
            angle = 90;
            sprite = &m_wall.getSprite("1side");
            break;
        case W_LEFT | W_TOP:
            angle = 90;
            sprite = &m_wall.getSprite("2side");
            break;
        case W_LEFT | W_BOTTOM:
            angle = 180;
            sprite = &m_wall.getSprite("2side");
            break;
        case W_LEFT | W_BOTTOM | W_TOP:
            angle = 90;
            sprite = &m_wall.getSprite("3side");
            break;
        case W_RIGHT:
            angle = 270;
            sprite = &m_wall.getSprite("1side");
            break;
        case W_RIGHT | W_TOP:
            angle = 0;
            sprite = &m_wall.getSprite("2side");
            break;
        case W_RIGHT | W_BOTTOM:
            angle = 270;
            sprite = &m_wall.getSprite("2side");
            break;
        case W_RIGHT | W_BOTTOM | W_TOP:
            angle = 270;
            sprite = &m_wall.getSprite("3side");
            break;
        case W_RIGHT | W_LEFT:
            angle = 180;
            sprite = &m_wall.getSprite("2side_opp");
            break;
        case W_RIGHT | W_LEFT | W_TOP:
            angle = 0;
            sprite = &m_wall.getSprite("3side");
            break;
        case W_RIGHT | W_LEFT | W_BOTTOM:
            angle = 180;
            sprite = &m_wall.getSprite("3side");
            break;
        case W_RIGHT | W_LEFT | W_BOTTOM | W_TOP:
            angle = 0;
            sprite = &m_wall.getSprite("4side");
            break;
        default:
            /* unused */
            break;
    }
    block.setSpriteRotate((3.14159f / 180.0f) * angle);
    block.setSpriteInvert(false);
    block.setSprite(*sprite);
}

void Wall::updateWallTextures()
{
    std::unordered_map<std::pair<int, int>, uint32_t, PairKeyHash> bitmasks;
    for(auto x = m_blocks.begin(); x != m_blocks.end(); x++) {
        for(auto y = x->begin(); y != x->end(); y++) {
            SDL_Point pos = (*y)->getTilePos();
            std::pair<int, int> up(pos.x, pos.y + 1);
            std::pair<int, int> down(pos.x, pos.y - 1);
            std::pair<int, int> left(pos.x - 1, pos.y);
            std::pair<int, int> right(pos.x + 1, pos.y);
            bitmasks[up] |= W_BOTTOM;
            bitmasks[down] |= W_TOP;
            bitmasks[left] |= W_RIGHT;
            bitmasks[right] |= W_LEFT;
        }
    }
    for(auto x = m_blocks.begin(); x != m_blocks.end(); x++) {
        for(auto y = x->begin(); y != x->end(); y++) {
            SDL_Point pos = (*y)->getTilePos();
            std::pair<int, int> entry(pos.x, pos.y);
            if(bitmasks.find(entry) != bitmasks.end()) {
                setWallTexture(**y, bitmasks[entry]);
            } else {
                setWallTexture(**y, static_cast<uint32_t>(W_NONE));
            }
        }
    }
}
void Wall::updateRegion()
{
    const SDL_Rect& region = m_camera.getViewableRegion();
    const Sprite& normal = m_wall.getSprite("0side");
    const int x_start = region.x / normal.getWidth();
    const int x_end = x_start + m_tiles.x;
    bool updated = false;
    for(int x = x_start; x < x_end; x++) {
        if(x >= m_path.x) {
            std::vector<Block*> blocks;
            /* draws one screen above, the current screen, and one below. */
            const int screen_heights = 3;
            const int y_start = region.y / normal.getHeight() - m_tiles.y;
            const int y_end = y_start + screen_heights * m_tiles.y;
            for(int y = y_start; y < y_end; y++) {
                bool filled = abs(y - m_path.y) > m_tunnel_size ? true : false;
                filled &= rand() % 10 == 0 ? false : true;
                if(filled) {
                    SDL_Point pos;
                    pos.x = x * normal.getWidth();
                    pos.y = y * normal.getWidth();
                    SDL_Point tile_pos;
                    tile_pos.x = x;
                    tile_pos.y = y;
                    blocks.push_back(new Block(m_b2world, &normal, pos, tile_pos, false));
                }
            }
            m_blocks.push_back(blocks);
            m_path.y += rand() % 2 ? 1 : -1;
            m_path.x++;
            m_tunnel_size = (4 - m_path.x / 20) + 3 + (rand() % 2) * ((
                                rand() % 2) ? -1 : 1);
            if(m_tunnel_size < 2) {
                m_tunnel_size = 2 + rand() % 2;
            }
            updated = true;
        }
    }
    m_blocks.erase(std::remove_if(m_blocks.begin(), m_blocks.end(),
    [&](const std::vector<Block*>& blocks) -> bool {
        const Block* block = blocks.front();
        const int pixels_x = 100;
        if(block) {
            SDL_Point pos = block->getPos();
            SDL_Rect region = m_camera.getViewableRegion();
            bool invisible = pos.x < region.x - pixels_x;
            if(invisible) {
                for(auto y = blocks.begin(); y != blocks.end(); y++) {
                    delete *y;
                }
            }
            updated |= invisible;
            return invisible;
        }
        return true;
    }), m_blocks.end());
    if(updated) {
        updateWallTextures();
    }
}

void Wall::onRender(SDL_Renderer* ren)
{
    for(auto x = m_blocks.begin(); x != m_blocks.end(); x++) {
        for(auto y = x->begin(); y != x->end(); y++) {
            (*y)->onRender(ren, m_camera);
        }
    }
}
