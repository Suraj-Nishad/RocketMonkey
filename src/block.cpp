#include "block.h"
#include "wall.h"

Block::Block(b2World* b2world, const Sprite* sprite, SDL_Point pos,
             SDL_Point tile_pos, bool filled)
    : GameObject(b2world, sprite, pos, b2_staticBody), m_tile_pos(tile_pos)
{
}
