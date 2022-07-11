#pragma once

#include "Objects/movingObj/Enemy.h"
#include "Attack.h"

class RobotEnemy : public Enemy 
{
public:
    RobotEnemy(const sf::Vector2f&, b2World&, const sf::Vector2f&);
  
    AnimationStatus_t move(sf::Vector2f);

    Objects_t getBodyType() const override { return ROBOT_ENEMY; }

    void draw(sf::RenderWindow& window, sf::Time)override;

private:
    Side_t FindDirectionToShoot(sf::Vector2f);
    static bool m_registerIt;
    Attack m_attack;
};