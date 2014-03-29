#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL.h>
#include "game_object.h"

class Camera
{
private:
    SDL_Rect m_screen;
    const GameObject& m_target;
public:
    Camera(const SDL_Rect& screen, const GameObject& target);
    const SDL_Rect& getViewableRegion() const {
        return m_screen;
    };
    void updatePosition();
};
#endif
