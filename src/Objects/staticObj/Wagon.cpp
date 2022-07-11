#include "Objects/staticObj/Wagon.h"

// connect Wagon to factory.
bool Wagon::m_registerIt = Factory<StaticObject>::registerObject(WAGON, [](const sf::Vector2f &pos,
                                                            b2World &world, const sf::Vector2f& dimension) -> std::shared_ptr<StaticObject>
{
    return std::make_shared<Wagon>(pos, world, dimension);
});

//-----------------------------------------------
Wagon::Wagon(const sf::Vector2f &pos, b2World &world, const sf::Vector2f& dimension)
    :StaticObject(ResourceManager::instance().getSprite(Textures_t::WAGON_T), pos, world, dimension, false, b2_dynamicBody)
{
    setFixedRotation(true);
    setUserData();
}
