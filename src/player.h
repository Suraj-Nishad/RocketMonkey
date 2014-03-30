#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "game_object.h"
#include "sprite.h"

class Player : public GameObject
{
public:
    Player(b2World* b2world, const SDL_Point& pos, const Sprite& sprite);
    void onLoop();
    void startContact(GameObject*);
    void endContact(GameObject*);
};

#endif
