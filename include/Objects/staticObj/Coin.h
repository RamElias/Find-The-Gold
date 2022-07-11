#pragma once

#include "StaticObject.h"

class Coin : public StaticObject
{
public:
    Coin(const sf::Vector2f & pos, b2World & world, const sf::Vector2f&);

    Objects_t getBodyType() const override { return COIN; }

private:
    static bool m_registerIt;
};