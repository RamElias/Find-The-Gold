#include "Objects/GameObject.h"

GameObject::GameObject(const sf::Sprite & sprite, const sf::Vector2f & pos, b2World & world,
                        const sf::Vector2f& dimension, std::unique_ptr<Animation> animation) :
                       m_body(nullptr), m_sprite(sprite), m_world(world), m_pos(pos)
{
    m_sprite.setScale(WINDOW_SIZE.first / (m_sprite.getGlobalBounds().width * dimension.x),
                      WINDOW_SIZE.second / (m_sprite.getGlobalBounds().height * dimension.y));

    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

    m_sprite.setPosition(m_pos.x * WINDOW_SIZE.first / dimension.x + m_sprite.getGlobalBounds().width / 2,
                         m_pos.y * WINDOW_SIZE.second / dimension.y + m_sprite.getGlobalBounds().height / 2);

    m_animation = std::move(animation);
}

//-----------------------------------------------
GameObject::~GameObject() 
{
    m_body->SetUserData(nullptr);
    m_world.DestroyBody(m_body);
}

//-----------------------------------------------
void GameObject::setPos(const sf::Vector2f & pos) 
{
    m_sprite.setPosition(pos);
    m_pos = pos;
}

//-----------------------------------------
void GameObject::setRotation() {
    m_sprite.rotate(m_body->GetAngle());
}

//-----------------------------------------
void GameObject::rigidBody(b2World& world, const b2Vec2& pos, Shape_t shape,
                           float size, float density, float friction, float groupIndex,
                           float restitution, bool sensor, const b2BodyType bodyType)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(pos.x, pos.y);
    m_body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    b2PolygonShape polygonShape;

    if (shape == Shape_t::CIRCLE_SHAPE) {
        circleShape.m_radius = size - b2_polygonRadius;
        fixtureDef.shape = &circleShape;
    }
    else if (shape == Shape_t::POLYGON_SHAPE) {
        polygonShape.SetAsBox(size - b2_polygonRadius, size - b2_polygonRadius);
        fixtureDef.shape = &polygonShape;
    }

    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.isSensor = sensor;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = groupIndex;

    m_body->CreateFixture(&fixtureDef);
}

//-----------------------------------------
void GameObject::update(sf::Time deltaTime, const sf::Vector2f & dimension) 
{
    //update the animation
    if(m_animation)
        m_animation->update(deltaTime);

    // seting the sprite to the physical world.
    auto position = getBodyPos();
    position.x *= WINDOW_SIZE.first / dimension.x;
    position.y *= WINDOW_SIZE.second / dimension.y;
    position.x += m_sprite.getGlobalBounds().width / 2;
    position.y += m_sprite.getGlobalBounds().height / 2;
    setPos({ position.x, position.y});
}
