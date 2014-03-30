#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <Box2D/Box2D.h>

class Contact : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif
