#pragma once

#include "StaticObject.h"

// A class that represents a wall object.

class Wagon : public StaticObject
{
public:
    Wagon(const sf::Vector2f & pos, b2World & world, const sf::Vector2f&);
    Objects_t getBodyType() const override { return WAGON; }

private:
    static bool m_registerIt;
};