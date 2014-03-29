#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include "CEvent.h"
#include "spritefile.h"

class CApp : public CEvent
{
private:
    bool            Running;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    CApp();

    int OnExecute();

public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();
    void OnExit();
};

#endif
