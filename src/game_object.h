#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <SDL.h>
#include "camera.h"
#include <Box2D/Box2D.h>
#include "sprite.h"

class GameObject
{
private:
    b2Body* m_body;
    b2World* m_world;
    const Sprite* m_sprite;
public:
    GameObject(b2World* world, const Sprite* sprite, SDL_Point pos,
               b2BodyType body_type);
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
    const Sprite* getSprite() const {
        return m_sprite;
    };
    void setSprite(const Sprite& sprite) {
        m_sprite = &sprite;
    }
    void setSpriteRotate(float rad_angle) {
        m_body->SetTransform(m_body->GetPosition(), rad_angle);
    }
    virtual void startContact(GameObject*) {};
    virtual void endContact(GameObject*) {};
    const SDL_Point applyCamera(const Camera& cam) const;
    virtual void onRender(SDL_Renderer* ren, const Camera& cam) const;
    virtual ~GameObject();
};

#endif
