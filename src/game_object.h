#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <SDL.h>
#include "camera.h"
#include <Box2D/Box2D.h>

class GameObject
{
private:
    b2Body* m_body;
    b2World* m_world;
public:
    GameObject(b2World* world, SDL_Point pos, b2BodyType body_type);
    SDL_Point getPos() const;
    void forceVertical(int n) {
        m_body->ApplyLinearImpulse(b2Vec2(0, n), m_body->GetWorldCenter(), true);
    }
    void forceHorizontal(int n) {
        m_body->ApplyLinearImpulse(b2Vec2(n, 0), m_body->GetWorldCenter(), true);
    }
    b2Body* getBody() const {
        return m_body;
    } ;
    virtual void onRender(SDL_Renderer* ren, const Camera& cam) const = 0;
    const SDL_Point applyCamera(const Camera& cam) const;
    virtual ~GameObject();
};

#endif
