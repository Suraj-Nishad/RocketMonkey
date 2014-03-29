#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "game_object.h"
#include "sprite.h"

class Player : public GameObject
{
private:
    const Sprite& m_sprite;
public:
    Player(const SDL_Point& pos, const Sprite& sprite);
    void onRender(SDL_Renderer* ren, const Camera& cam) const;
};

#endif
