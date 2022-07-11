#include "Objects/staticObj/gift/BulletGift.h"

// connect BulletGift to factory.
bool BulletGift::m_registerIt = Factory<Gift>::registerObject(BULLET_GIFT, [](const sf::Vector2f& pos,
    b2World& world, const sf::Vector2f& dimension) -> std::shared_ptr<Gift>
    {
        return std::make_shared<BulletGift>(pos, world, dimension);
    });

//-----------------------------------------------
BulletGift::BulletGift(const sf::Vector2f& pos, b2World& world, const sf::Vector2f& dimension)
    :Gift(ResourceManager::instance().getSprite(Textures_t::BULLET_GIFT_T), pos, world, dimension,
        std::make_unique<Animation>(ResourceManager::instance().animationData(AMMO_GIFT_D),
            AnimationStatus_t::Round,
            getSprite(), dimension))
{
    setUserData();
}