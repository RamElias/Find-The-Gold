#include "Objects/staticObj/Coin.h"

// connect Coin to factory.
bool Coin::m_registerIt = Factory<StaticObject>::registerObject(COIN, [](const sf::Vector2f &pos,
                                                            b2World &world, const sf::Vector2f& dimension) -> std::shared_ptr<StaticObject>
{
    return std::make_shared<Coin>(pos, world, dimension);
});

//-----------------------------------------------
Coin::Coin(const sf::Vector2f &pos, b2World &world, const sf::Vector2f& dimension)
    :StaticObject(ResourceManager::instance().getSprite(Textures_t::COIN_T), pos, world, dimension, false, b2_staticBody,
                    std::make_unique<Animation>(ResourceManager::instance().animationData(COIN_D),
                    AnimationStatus_t::Round,
                    getSprite(), dimension))
{
    setUserData();
}
