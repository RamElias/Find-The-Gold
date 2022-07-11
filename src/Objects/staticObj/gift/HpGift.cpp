#include "Objects/staticObj/gift/HpGift.h"

// connect HpGift to factory.
bool HpGift::m_registerIt = Factory<Gift>::registerObject(HP_GIFT, [](const sf::Vector2f& pos,
    b2World& world, const sf::Vector2f& dimension) -> std::shared_ptr<Gift>
    {
        return std::make_shared<HpGift>(pos, world, dimension);
    });

//-----------------------------------------------
HpGift::HpGift(const sf::Vector2f& pos, b2World& world, const sf::Vector2f& dimension)
    :Gift(ResourceManager::instance().getSprite(Textures_t::HP_GIFT_T), pos, world, dimension,
            std::make_unique<Animation>(ResourceManager::instance().animationData(HP_GIFT_D),
            AnimationStatus_t::Round,
            getSprite(), dimension))
{
    setFixedRotation(true);
    setUserData();
}

