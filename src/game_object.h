#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <SDL.h>

class GameObject
{
protected:
    SDL_Point m_pos;
public:
    GameObject(SDL_Point pos);
    const SDL_Point& getPos() const {
        return m_pos;
    };
    void moveX(int x) {
        m_pos.x += x;
    };
    void moveY(int y) {
        m_pos.y += y;
    };
};

#endif
