#include "Objects/movingObj/Bullet.h"


Bullet::Bullet(const sf::Vector2f & pos, b2World & world, const sf::Vector2f & dimension,
               const Side_t& sideToShoot, const float & hitPoint, const float & desiredVel,const int toHit)
    :m_sideToShoot(sideToShoot), m_desiredVel(desiredVel), m_hitPoint(hitPoint),
               MovingObject(ResourceManager::instance().getSprite(Textures_t::BULLET_T), pos, world,dimension)
{

    //calc the direction nedded for thr bullets
    auto to_add = 0;
    if (m_sideToShoot == Side_t::RIGHT) 
    {
        m_desiredVel *= 1;
        to_add = getGlobalBounds().width / 2;
    }
    else 
    {
        m_desiredVel *= -1;
        to_add -= getGlobalBounds().width / 2;
        opposite(Side_t::LEFT);
    }

    // adjust to Physical position.
    auto objectPosition = sf::Vector2f{ ((pos.x + to_add) * dimension.x - getGlobalBounds().width / 2) / WINDOW_SIZE.first,
                        ((pos.y - getGlobalBounds().height/4) * dimension.y - getGlobalBounds().height / 2) / WINDOW_SIZE.second };

    b2Vec2 position(objectPosition.x, objectPosition.y);

    getSprite().setScale(getSprite().getScale().x / 3, getSprite().getScale().y / 5);

    rigidBody(world, position, CIRCLE_SHAPE, 0.48 / 3, 2.f, 2.f, toHit, 0, true, b2_dynamicBody);

    setUserData();

    setFixedRotation(true);
    
    m_clock.restart();
}

//-----------------------------------------------
bool Bullet::shoot()
{
    auto deltaTime = m_clock.getElapsedTime();

    if (deltaTime.asSeconds() >= BULLET_DISTANCE)
        m_disposed = true; 

    moveX(m_desiredVel);
    moveY(ANTI_GRAVITY.y);
    
    return m_disposed;
}

//-----------------------------------------------
void Bullet::startContact(Wall*)
{
    m_disposed = true;
}