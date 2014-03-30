#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <SDL.h>
#include "game_object.h"

class Wall;
class Block : public GameObject
{
private:
    const SDL_Point m_tile_pos;
public:
    Block(b2World* b2world, const Sprite* sprite, SDL_Point pos, SDL_Point tile_pos,
          bool filled);
    const SDL_Point& getTilePos() const {
        return m_tile_pos;
    };
};

#endif
