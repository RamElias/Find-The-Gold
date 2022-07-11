#include "Attack.h"

Attack::Attack(const sf::Vector2f & dimension, const int hit) 
    : m_dimension(dimension), m_hit(hit), m_fireRate(FIRE_RATE), m_bulletDamage(BULLET_DAMAGE)
{}

//-----------------------------------------------
//function for shoot
bool Attack::shoot(sf::Vector2f pos, b2World & world, Side_t side)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_fireRate) 
    {
        m_bullets.emplace_back(std::make_unique<Bullet>(pos, world, m_dimension,
                                                        side, m_bulletDamage, m_bulletVelocity, m_hit));
        m_clock.restart();
        return true;
    } 
    return false;
}

//-----------------------------------------------
void Attack::setFireRate(const float & fireRate)
{
    m_fireRate = fireRate;
}

//-----------------------------------------------
void Attack::setBulletVelocity(const float & bulletVelocity)
{
    m_bulletVelocity = bulletVelocity;
}

//-----------------------------------------------
void Attack::setBulletDamage(const float& bulletDamage) 
{
    m_bulletDamage = bulletDamage;
}

//-----------------------------------------------
//make the bullets shoots and erase the last one
void Attack::bulletCheck()
{
   for (size_t i = 0; i < m_bullets.size(); i++) 
       if (m_bullets[i]->shoot()) 
       {
            m_bullets.erase(m_bullets.begin());
            --i;
       }
}

//-----------------------------------------------
//draw the bullet
void Attack::drawBullet(sf::RenderWindow & window, sf::Time deltaTime) 
{
    for (auto& bullet : m_bullets) 
    {
        bullet->draw(window, deltaTime);
        bullet->update(deltaTime, m_dimension);
    }
}