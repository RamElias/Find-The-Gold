#include "Objects/staticObj/Wall.h"

// connect Wall to factory.
bool Wall::m_registerIt = Factory<StaticObject>::registerObject(WALL, [](const sf::Vector2f &pos,
                                                            b2World &world, const sf::Vector2f& dimension) -> std::shared_ptr<StaticObject>
{
    return std::make_shared<Wall>(pos, world, dimension);
});

//-----------------------------------------------
Wall::Wall(const sf::Vector2f &pos, b2World &world, const sf::Vector2f& dimension)
    :StaticObject(ResourceManager::instance().getSprite(Textures_t::WALL_T), pos, world, dimension, false, b2_staticBody)
{
    setUserData();
}
