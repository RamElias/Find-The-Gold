#include "Objects/staticObj/Gate.h"

// connect Gate to factory.

bool Gate::m_registerIt = Factory<StaticObject>::registerObject(GATE, [](const sf::Vector2f &pos,
                                                            b2World &world, const sf::Vector2f& dimension) -> std::shared_ptr<StaticObject>
{
    return std::make_shared<Gate>(pos, world, dimension);
});

//-----------------------------------------------
Gate::Gate(const sf::Vector2f &pos, b2World &world, const sf::Vector2f& dimension)
    :StaticObject(ResourceManager::instance().getSprite(Textures_t::GATE_T), pos, world, dimension, false, b2_staticBody)
{
    setUserData();
}
