#ifndef _SPRITEFILE_H_
#define _SPRITEFILE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include <stdint.h>
#include "sprite.h"

class SpriteFile
{
private:
    SDL_Texture* m_texture;
    std::unordered_map<std::string, const Sprite*> m_sprites;
public:
    void onLoad(SDL_Renderer* ren, const std::string& sprite_file);
    const Sprite* getSprite(std::string name) {
        return m_sprites[name];
    };
    SDL_Texture* getTexture() const {
        return m_texture;
    };

};

#endif
