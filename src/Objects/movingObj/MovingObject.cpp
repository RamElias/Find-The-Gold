#include "Objects/movingObj/MovingObject.h"

MovingObject::MovingObject(const sf::Sprite& sprite, const sf::Vector2f& pos, b2World& world,
    const sf::Vector2f& dimension, std::unique_ptr<Animation> animation)
    :GameObject(sprite, pos, world, dimension, std::move(animation)), m_side(Side_t::RIGHT),
    m_hp(MAX_HP)
{}

//-----------------------------------------------
void MovingObject::draw(sf::RenderWindow& window, sf::Time deltaTime){
    GameObject::draw(window);
}

//-----------------------------------------------
//move on the x 
void MovingObject::moveX(float desiredVelX) 
{
    b2Vec2 vel = getBodyLinearVelocity();
    float velChangeX = desiredVelX - vel.x;
    float impulseX = getBodyMass() * velChangeX; 
    getBody()->ApplyLinearImpulse(b2Vec2(impulseX, 0), getBody()->GetWorldCenter(), true);
}

//-----------------------------------------------
//move on the y
void MovingObject::moveY(float desiredVelY) 
{
    b2Vec2 vel = getBodyLinearVelocity();
    float velChangeY = desiredVelY - vel.y;
    float impulseY = getBodyMass() * velChangeY; 
    getBody()->ApplyLinearImpulse(b2Vec2(0, impulseY), getBody()->GetWorldCenter(), true);
}

//-----------------------------------------------
//change sprite to right direction
Side_t MovingObject::opposite(enum Side_t side)
{
    if(side != m_side) 
    {
        getSprite().scale(-1, 1);
        m_side = side;
    }
    return m_side;
}

//-----------------------------------------------
void MovingObject::decreaseHP(int amount)
{
    m_hp -= amount;
    if (m_hp < 0)
        m_hp = 0;
}

//-----------------------------------------------
void MovingObject::incHP()
{
    m_hp = MAX_HP;
}

//-----------------------------------------------
bool MovingObject::isInjured()
{
    auto temp = m_injured;
    m_injured = false;
    return temp;
}

//-----------------------------------------------
bool MovingObject::isShoot()
{
    auto temp = m_shoot;
    m_shoot = false;
    return temp;
}
