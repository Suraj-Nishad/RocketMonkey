#include "CApp.h"

CApp::CApp()
{
    m_wall = NULL;
    m_sprites = NULL;
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

void CApp::OnKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym) {
        case SDLK_LEFT:
            //m_player->forceHorizontal(-50);
            break;
        case SDLK_RIGHT:
            //m_player->forceHorizontal(50);
            break;
        case SDLK_UP:
            m_player->forceVertical(2);
            break;
        case SDLK_DOWN:
            //m_player->forceVertical(-50);
            break;
    }
}

bool CApp::OnInit()
{
    m_screen.w = 640;
    m_screen.h = 480;
    m_screen.x = 0;
    m_screen.y = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }
    if((window = SDL_CreateWindow("RocketMonkey", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, m_screen.w, m_screen.h,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL) {
        return false;
    }
    if((renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        return false;
    }
    SDL_Point player_pos;
    b2Vec2 gravity(0, -9.8); //normal earth gravity, 9.8 m/s/s straight down!
    box2d_world = new b2World(gravity);
    player_pos.x = 10;
    player_pos.y = m_screen.h / 2;
    m_sprites = new SpriteFile(renderer, "img/player.json");
    m_player = new Player(box2d_world, player_pos, m_sprites->getSprite("default"));
    m_camera = new Camera(m_screen, *m_player);
    m_wall = new Wall(box2d_world, renderer, m_screen, *m_camera);
    m_current_time = m_last_time = SDL_GetTicks();
    m_contact = new Contact();
    box2d_world->SetContactListener(m_contact);
    return true;
}

void CApp::OnLoop()
{
    m_current_time = SDL_GetTicks();
    int32 iterations = 3;
    m_camera->updatePosition();
    m_wall->updateRegion();
    m_player->onLoop();
    box2d_world->Step((m_current_time - m_last_time) / 1000.0f, iterations,
                      iterations);
    m_last_time = m_current_time;
}

void CApp::OnRender()
{
    SDL_Texture* texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, m_screen.w, m_screen.h);
    SDL_SetRenderTarget(renderer, texTarget);
    SDL_RenderClear(renderer);
    m_wall->onRender(renderer);
    m_player->onRender(renderer, *m_camera);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texTarget);
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
    delete m_wall;
    delete m_sprites;
    delete box2d_world;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

