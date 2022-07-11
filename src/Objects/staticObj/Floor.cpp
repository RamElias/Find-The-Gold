#include "Objects/staticObj/Floor.h"

// connect Floor to factory.
bool Floor::m_registerIt = Factory<StaticObject>::registerObject(FLOOR, [](const sf::Vector2f &pos,
                                                            b2World &world, const sf::Vector2f& dimension) -> std::shared_ptr<StaticObject>
{
    return std::make_shared<Floor>(pos, world, dimension);
});

//-----------------------------------------------
Floor::Floor(const sf::Vector2f &pos, b2World &world, const sf::Vector2f& dimension)
    :StaticObject(ResourceManager::instance().getSprite(Textures_t::FLOOR_T), pos, world, dimension, false, b2_staticBody)
{
    setUserData();
}
