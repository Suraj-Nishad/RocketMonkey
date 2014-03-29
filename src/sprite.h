#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SpriteFile;
class Sprite
{
private:
    const SpriteFile& m_sprite_file;
    const std::string m_name;
    const SDL_Rect m_clip;
public:
    Sprite(const SpriteFile& f, std::string name, const SDL_Rect& clip);
    void onRender(SDL_Renderer* ren, uint32_t x, uint32_t y) const;
};

#endif
