#pragma once

#include "StaticObject.h"

class Gate : public StaticObject
{
public:
    Gate(const sf::Vector2f & pos, b2World & world, const sf::Vector2f&);
    Objects_t getBodyType() const override { return GATE; }

private:
    static bool m_registerIt;
};