#include "contact.h"
#include "game_object.h"

void Contact::BeginContact(b2Contact* contact)
{
    GameObject* dataA = static_cast<GameObject*>
                        (contact->GetFixtureA()->GetBody()->GetUserData());
    GameObject* dataB = static_cast<GameObject*>
                        (contact->GetFixtureB()->GetBody()->GetUserData());
    if(dataA) {
        dataA->startContact(dataB);
    }
    if(dataB) {
        dataB->startContact(dataA);
    }
}

void Contact::EndContact(b2Contact* contact)
{
    GameObject* dataA = static_cast<GameObject*>
                        (contact->GetFixtureA()->GetBody()->GetUserData());
    GameObject* dataB = static_cast<GameObject*>
                        (contact->GetFixtureA()->GetBody()->GetUserData());
    if(dataA) {
        dataA->endContact(dataB);
    }
    if(dataB) {
        dataB->endContact(dataA);
    }
}
