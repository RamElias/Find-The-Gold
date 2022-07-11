#include "Objects/movingObj/DinoEnemy.h"
#include "Macros.h"

// connect DinoEnemy to factory.

bool DinoEnemy::m_registerIt = Factory<Enemy>::registerObject(DINO_ENEMY, [](const sf::Vector2f &pos, b2World &world, const sf::Vector2f & dimension) -> std::shared_ptr<Enemy> 
{
    return std::make_shared<DinoEnemy>(pos, world, dimension);
});

//-----------------------------------------------
DinoEnemy::DinoEnemy(const sf::Vector2f& pos, b2World& world, const sf::Vector2f & dimension):
    Enemy(ResourceManager::instance().getSprite(Textures_t::DINO_ENEMY_T), pos, world, dimension,
          std::make_unique<Animation>(ResourceManager::instance().animationData(DINO_ENEMY_D),
                                      AnimationStatus_t::Idle,
                                      getSprite(), dimension))
{}

//-----------------------------------------------
AnimationStatus_t DinoEnemy::move(sf::Vector2f playerPosition){

    b2Vec2 desiredVel(0,0);
    if (getBody()->GetLinearVelocity().x >= 0)
        desiredVel.x = ENEMY_VELOCITY;

    else
        desiredVel.x = -ENEMY_VELOCITY;

    setDirection(desiredVel);
    return Enemy::move(playerPosition);
}
