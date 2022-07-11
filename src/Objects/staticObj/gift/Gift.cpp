#include "Objects/staticObj/gift/Gift.h"

//-----------------------------------------------
Gift::Gift(const sf::Sprite& sprite, const sf::Vector2f& pos, b2World& world, const sf::Vector2f& dimension, std::unique_ptr<Animation> animation)
    : StaticObject(sprite, pos, world, dimension, false, b2_staticBody,std::move(animation)) 
{
    setUserData();
}
