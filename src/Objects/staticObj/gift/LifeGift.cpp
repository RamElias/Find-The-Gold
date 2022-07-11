#include "Objects/staticObj/gift/LifeGift.h"

// connect LifeGift to factory.
bool LifeGift::m_registerIt = Factory<Gift>::registerObject(LIFE_GIFT, [](const sf::Vector2f& pos,
    b2World& world, const sf::Vector2f& dimension) -> std::shared_ptr<Gift>
    {
        return std::make_shared<LifeGift>(pos, world, dimension);
    });

//-----------------------------------------------
LifeGift::LifeGift(const sf::Vector2f& pos, b2World& world, const sf::Vector2f& dimension)
    :Gift(ResourceManager::instance().getSprite(Textures_t::LIFE_GIFT_T), pos, world, dimension,
        std::make_unique<Animation>(ResourceManager::instance().animationData(LIFE_GIFT_D),
            AnimationStatus_t::Round,
            getSprite(), dimension))
{
    setUserData();
}