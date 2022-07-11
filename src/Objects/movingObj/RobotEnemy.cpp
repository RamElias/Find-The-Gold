#include "Objects/movingObj/RobotEnemy.h"

// connect RobotEnemy to factory.

bool RobotEnemy::m_registerIt = Factory<Enemy>::registerObject(ROBOT_ENEMY, [](const sf::Vector2f& pos,
        b2World& world, const sf::Vector2f& dimension) -> std::shared_ptr<Enemy>
    {

        return std::make_shared<RobotEnemy>(pos, world, dimension);
    });

RobotEnemy::RobotEnemy(const sf::Vector2f& pos, b2World& world, const sf::Vector2f& dimension) 
    :m_attack(dimension,-1),
    Enemy(ResourceManager::instance().getSprite(Textures_t::ROBOT_ENEMY_T), pos, world, dimension,
          std::make_unique<Animation>(ResourceManager::instance().animationData(ROBOT_ENEMY_D),
                                      AnimationStatus_t::Walk,
                                      getSprite(), dimension))
{
    m_attack.setFireRate(ROBOT_FIRE_RATE);
    m_attack.setBulletVelocity(BULLET_VELOCITY);
    m_attack.setBulletDamage(ENEMY_BULLET_DAMAGE);
}

//-----------------------------------------------
AnimationStatus_t RobotEnemy::move(sf::Vector2f playerPosition) 
{
    b2Vec2 desiredVel(0, 0);

    // Checks the palyer is near so he will start shooting
    if ( getPos().y - playerPosition.y > -PLAYER_ENEMY_RANGE && getPos().y - playerPosition.y < PLAYER_ENEMY_RANGE 
        &&  (getPos().x - playerPosition.x < ENEMY_SHOOTING_RANGE && getPos().x - playerPosition.x > -ENEMY_SHOOTING_RANGE) )
    {
        if (getMovement() != AnimationStatus_t::Death) 
        {
            if (m_attack.shoot(getPos(), *getBody()->GetWorld(), FindDirectionToShoot(playerPosition)))
                setShoot(); 
        }
    }

    // set directon
    else if (getBody()->GetLinearVelocity().x >= 0)
        desiredVel.x = ENEMY_VELOCITY;
    else
        desiredVel.x = -ENEMY_VELOCITY;

    m_attack.bulletCheck();
    setDirection(desiredVel);
    return Enemy::move(playerPosition);
}

//-----------------------------------------------
Side_t RobotEnemy::FindDirectionToShoot(sf::Vector2f playerPosition)
{
    if (playerPosition.x < getPos().x)
        return Side_t::LEFT;
    return Side_t::RIGHT;
}

//-----------------------------------------------
void RobotEnemy::draw(sf::RenderWindow& window,sf::Time deltaTime) 
{
    MovingObject::draw(window, deltaTime);
    m_attack.drawBullet(window, deltaTime);
}
