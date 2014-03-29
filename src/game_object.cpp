#include "game_object.h"

static float pixel2meter(int pixel)
{
    return 0.02f * pixel;
}

static int meter2pixel(float meter)
{
    return 50 * meter;
}

GameObject::GameObject(b2World* b2world, SDL_Point pos, b2BodyType body_type)
    : m_world(b2world)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = body_type;
    myBodyDef.position.Set(pixel2meter(pos.x), pixel2meter(pos.y));
    myBodyDef.angle = 0;
    m_body = b2world->CreateBody(&myBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(pixel2meter(50) / 2, pixel2meter(50) / 2);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    m_body->CreateFixture(&boxFixtureDef);
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
