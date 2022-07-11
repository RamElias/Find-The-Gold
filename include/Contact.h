#pragma once

#include "box2d/box2d.h"
#include "Macros.h"
#include "Objects/movingObj/Player.h"
#include <Objects/staticObj/Wall.h>

// A class that responsible for collisions in b2world.
class Contact : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact) override;

private:
    void playerStartContact(Player *, GameObject *);

    void enemyStartContact(Enemy *, GameObject *);

    void bulletStartContact(Bullet *, GameObject *);
};
