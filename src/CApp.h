#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include "CEvent.h"
#include "spritefile.h"
#include "wall.h"
#include "player.h"
#include "camera.h"
#include "contact.h"
#include <Box2D/Box2D.h>

class CApp : public CEvent
{
private:
    unsigned int m_last_time, m_current_time;
    b2World* box2d_world;
    bool Running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Wall* m_wall;
    SpriteFile* m_sprites;
    Player* m_player;
    Camera* m_camera;
    Contact* m_contact;
    SDL_Rect m_screen;
public:
    CApp();
    int OnExecute();
public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();
    void OnKeyDown(SDL_Keycode sym, SDL_Keymod mod);
    void OnRender();

    void OnCleanup();
    void OnExit();
};

#endif
