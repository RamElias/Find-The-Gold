#include "Objects/movingObj/Enemy.h"

//-----------------------------------------------
Enemy::Enemy(const sf::Sprite & sprite, const sf::Vector2f & pos, b2World & world, const sf::Vector2f & dimension,
             std::unique_ptr<Animation> animation) :
    MovingObject(sprite, pos, world, dimension,
                 std::move(animation)), m_dir(0,0), m_hitted(false)
{
    b2Vec2 position(pos.x, pos.y);

    rigidBody(world, position, CIRCLE_SHAPE, 0.48f, 2.f, 0.f, -1, 0.2f, false, b2_dynamicBody);

    setUserData();

    setFixedRotation(true);
}

//-----------------------------------------------
//move the enemy and change his animation to the animation nedded
AnimationStatus_t Enemy::move(sf::Vector2f playerPosition) 
{
    if (m_movement != AnimationStatus_t::Death) 
    {
        if (m_dir.x == 0) 
        {
            m_movement = AnimationStatus_t::Shoot;

            if (playerPosition.x < getPos().x)
                opposite(Side_t::LEFT);
            else
                opposite(Side_t::RIGHT);
        }
        else
            m_movement = AnimationStatus_t::Walk;

        if (m_hitted)
        {
            m_movement = AnimationStatus_t::Hurt;
            moveX(ENEMY_HIT * m_side);
            moveY(ENEMY_HIT);
            m_hitted = false;
        }

        if (getPos().y - playerPosition.y > -PLAYER_ENEMY_RANGE && getPos().y - playerPosition.y < PLAYER_ENEMY_RANGE
            && m_movement != AnimationStatus_t::Shoot) 
        {
            if (playerPosition.x < getPos().x) 
                m_dir.x = -2;
            else 
                m_dir.x = 2;
            
        }
        if (m_dir.y < 0 && m_movement != AnimationStatus_t::Shoot) 
        {
            moveY(m_dir.y);
        }
        else if (m_dir.x < 0 && m_movement != AnimationStatus_t::Shoot) 
        {
            moveX(m_dir.x);
            opposite(Side_t::LEFT);
        }

        else if (m_dir.x > 0 && m_movement != AnimationStatus_t::Shoot) 
        {
            moveX(m_dir.x);
            opposite(Side_t::RIGHT);
        }
        else {
            moveX(0);
        }
    }
    else
        moveX(0);

    setAnimationStatus(m_movement);

    return m_movement;
}

//-----------------------------------------------
void Enemy::setDirection(const b2Vec2 & dir)
{
    m_dir = dir;
}

//-----------------------------------------------
b2Vec2 Enemy::getDirection() const
{
    return m_dir;
}

//-----------------------------------------------
//handle contact with bullet
void Enemy::startContact(Bullet* bullet)
{
    if(getHP() <= 0)
        return;

    if (bullet->getBodyLinearVelocity().x >= 0)
        m_side *= 1;
    else
        m_side *= -1;

    m_hitted = true;
    setHP(getHP() - bullet->getHit());
    bullet->hit();
    setInjured();
}

//-----------------------------------------------
//set animation of dead
bool Enemy::isDead()
{
    if (getHP() <= 0)
    {
        if (!m_startTimer) 
        {
            m_startTimer = true;
            m_movement = AnimationStatus_t::Death;
            setAnimationStatus(m_movement);
            
            m_timer.restart();
        }
        return enemyDied();
    }
    return false;
}

//-----------------------------------------------
bool Enemy::enemyDied()
{
    auto time = m_timer.getElapsedTime().asSeconds();
    if (time <= 0.9)
        return false;
    return true;
}
