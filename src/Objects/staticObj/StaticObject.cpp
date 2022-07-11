#include "Objects/staticObj/StaticObject.h"

StaticObject::StaticObject(const sf::Sprite &sprite, const sf::Vector2f &pos, b2World & world, const sf::Vector2f& dimension,const bool sensorStatus, b2BodyType bodyType,
                           std::unique_ptr<Animation> animation)
                : GameObject(sprite, pos, world, dimension, std::move(animation)) 
{
    b2Vec2 position(pos.x, pos.y);

    rigidBody(world, position, POLYGON_SHAPE, 0.5, 2.f, 5.f, 0, 0, sensorStatus, bodyType);
}