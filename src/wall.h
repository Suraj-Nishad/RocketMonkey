#ifndef _WALL_H_
#define _WALL_H_

#include <SDL.h>
#include "spritefile.h"
#include <vector>
#include "block.h"
#include "camera.h"

class Wall
{
private:
    const SpriteFile& m_wall;
    int m_tunnel_size;
    SDL_Point m_path;
    SDL_Rect m_screen;
    SDL_Point m_tiles;
    const Camera& m_camera;
    std::vector<std::vector<Block*> > m_blocks;
public:
    Wall(const SDL_Rect& screen, const SpriteFile& wall, const Camera& camera);
    void updateRegion();
    void onRender(SDL_Renderer* ren);
    const SpriteFile& getSprites() const {
        return m_wall;
    };
    const Camera& getCamera() const {
        return m_camera;
    };
};

#endif
