#include "game_object.h"

static float pixel2meter(int pixel)
{
    return 0.02f * pixel;
}

static int meter2pixel(float meter)
{
    return 50 * meter;
}

GameObject::GameObject(b2World* b2world, const Sprite* sprite, SDL_Point pos,
                       b2BodyType body_type)
    : m_world(b2world), m_sprite(sprite)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = body_type;
    myBodyDef.position.Set(pixel2meter(pos.x), pixel2meter(pos.y));
    myBodyDef.angle = 0;
    m_body = b2world->CreateBody(&myBodyDef);
    m_body->SetUserData(this);
    b2PolygonShape boxShape;
    const SDL_Rect& r = m_sprite->getRect();
    boxShape.SetAsBox(pixel2meter(r.h) / 2, pixel2meter(r.w) / 2);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    b2Fixture* fixture = m_body->CreateFixture(&boxFixtureDef);
    fixture->SetUserData(this);
}

GameObject::~GameObject()
{
    m_world->DestroyBody(m_body);
    m_body = NULL;
}

SDL_Point GameObject::getPos() const
{
    SDL_Point pos;
    b2Vec2 vec = m_body->GetPosition();
    pos.x = meter2pixel(vec.x);
    pos.y = meter2pixel(vec.y);
    return pos;
}

const SDL_Point GameObject::applyCamera(const Camera& cam) const
{
    SDL_Point pt = getPos();
    SDL_Rect region = cam.getViewableRegion();
    pt.x -= region.x;
    pt.y -= region.y;
    return pt;
}

void GameObject::onRender(SDL_Renderer* ren, const Camera& cam) const
{
    getSprite()->onRender(ren, applyCamera(cam),
                          (180.0f / 3.14159f) * m_body->GetAngle());
}
