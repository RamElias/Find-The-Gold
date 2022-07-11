#pragma once

#include "Objects/movingObj/MovingObject.h"
#include <Objects/staticObj/Wall.h>

class Bullet : public MovingObject
{
public:
    Bullet(const sf::Vector2f &, b2World &, const sf::Vector2f &, const Side_t &,
           const float &, const float &,const int);

    Objects_t getBodyType()const override { return Objects_t::BULLET; }
    float getHit() const { return m_hitPoint;}
    void hit() { m_disposed = true; }
    bool shoot();

    void startContact(Wall*);

private:
    sf::Clock m_clock;
    bool m_disposed = false;
    float m_hitPoint;
    float m_desiredVel;
    Side_t m_sideToShoot;
};