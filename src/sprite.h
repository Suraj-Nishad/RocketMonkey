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
    void onRender(SDL_Renderer* ren, SDL_Point pt, float rad_angle,
                  bool m_invert) const;
    int getWidth() const {
        return m_clip.w;
    };
    int getHeight() const {
        return m_clip.h;
    };
    const SDL_Rect& getRect() const {
        return m_clip;
    }
};

#endif
