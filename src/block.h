#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <SDL.h>
#include "game_object.h"

class Wall;
class Block : public GameObject
{
private :
    bool m_filled;
    const Wall& m_wall;
public:
    Block(b2World* b2world, const Wall& wall, SDL_Point pos, bool filled);
    void onRender(SDL_Renderer* ren, const Camera& cam) const;
    const Wall& getWall() const {
        return m_wall;
    };
};

#endif
