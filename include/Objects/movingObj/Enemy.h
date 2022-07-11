#pragma once

#include "Objects/movingObj/MovingObject.h"
#include "Objects/movingObj/Bullet.h"
#include "Factory.h"

class Enemy : public MovingObject 
{
public:

    Enemy(const sf::Sprite & sprite, const sf::Vector2f & pos, b2World &,
          const sf::Vector2f &, std::unique_ptr<Animation> = nullptr);

    virtual AnimationStatus_t move(sf::Vector2f);
    void setDirection(const b2Vec2&);
    b2Vec2 getDirection()const;
    AnimationStatus_t getMovement() const { return m_movement; }
    int getHit()const { return m_hit; }
    bool isDead();
    void startContact(Bullet *);

private:
    bool m_startTimer = false;
    sf::Clock m_timer;
    float m_side = 1;
    int m_hit = 5;
    bool m_hitted;
    b2Vec2 m_dir;
    AnimationStatus_t m_movement = AnimationStatus_t::Idle;
    bool enemyDied();
};