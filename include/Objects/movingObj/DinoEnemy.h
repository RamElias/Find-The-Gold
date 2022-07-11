#pragma once

#include "Objects/movingObj/Enemy.h"


class DinoEnemy : public Enemy 
{
public:
    DinoEnemy(const sf::Vector2f &, b2World &, const sf::Vector2f&);
    
    AnimationStatus_t move(sf::Vector2f);

    Objects_t getBodyType() const override { return DINO_ENEMY; }

private:
    static bool m_registerIt;
};