#include "game_object.h"

GameObject::GameObject(SDL_Point pos)
    : m_pos(pos)
{
}

const SDL_Point GameObject::applyCamera(const Camera& cam) const
{
    SDL_Point pt = m_pos;
    SDL_Rect region = cam.getViewableRegion();
    pt.x -= region.x;
    pt.y -= region.y;
    return pt;
}
