#include "CApp.h"

CApp::CApp()
{
    Running = true;
}

void CApp::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CApp::OnExit()
{
    Running = false;
}

bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }
    if((window = SDL_CreateWindow("Test123", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL) {
        return false;
    }
    if((renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        return false;
    }
    return true;
}

void CApp::OnLoop()
{
}

void CApp::OnRender()
{
    SDL_RenderClear(renderer);
    SpriteFile test;
    test.onLoad(renderer, "img/wall.json");
    test.getSprite("red")->onRender(renderer, 100, 100);
    SDL_RenderPresent(renderer);
}

int CApp::OnExecute()
{
    if(OnInit() == false) {
        return -1;
    }
    SDL_Event Event;
    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();
    return 0;
}

void CApp::OnCleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

