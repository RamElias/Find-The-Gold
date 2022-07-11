#pragma once

#include "StaticObject.h"

class Floor : public StaticObject
{
public:
    Floor(const sf::Vector2f & pos, b2World & world, const sf::Vector2f&);
    Objects_t getBodyType() const override { return FLOOR; }

private:
    static bool m_registerIt;
};