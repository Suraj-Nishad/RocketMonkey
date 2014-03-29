#include "sprite.h"
#include "spritefile.h"
#include <SDL.h>

Sprite::Sprite(const SpriteFile& f, std::string name, const SDL_Rect& clip)
    : m_sprite_file(f), m_name(name), m_clip(clip)
{
}

void Sprite::onRender(SDL_Renderer* ren, SDL_Point pt) const
{
    SDL_Rect dst;
    dst.x = pt.x;
    dst.y = pt.y;
    dst.w = m_clip.w;
    dst.h = m_clip.h;
    SDL_RenderCopy(ren, m_sprite_file.getTexture(), &m_clip, &dst);
}
