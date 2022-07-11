#pragma once

#include "Macros.h"
#include "box2d/box2d.h"
#include "Animation.h"
#include "ResourceManager.h"

//class that is incharge of all object in the game
class GameObject 
{
public:
    GameObject(const sf::Sprite &, const sf::Vector2f &, b2World &, const sf::Vector2f &,
               std::unique_ptr<Animation> = nullptr);

    virtual ~GameObject();

    void draw(sf::RenderWindow &window) { window.draw(m_sprite); }

    void rigidBody(b2World& world, const b2Vec2& pos, Shape_t shape, float size,
                   float density, float friction, float groupIndex, float restitution,
                   bool sensor, const b2BodyType = b2_staticBody);

    void update(sf::Time deltaTime, const sf::Vector2f &);

    void setPos(const sf::Vector2f &);

    sf::Vector2f getPos() const { return m_sprite.getPosition(); }

    sf::FloatRect getGlobalBounds() const { return m_sprite.getGlobalBounds(); }

    void setRotation();

    void setBodyPos(b2Vec2 pos) { m_body->SetTransform(pos, m_body->GetAngle()); }

    void setUserData() { m_body->SetUserData(this); }

    void setFixedRotation(bool status) { m_body->SetFixedRotation(status); };

    void setAnimationStatus(enum AnimationStatus_t status) { m_animation->setStatus(status); }

    b2Vec2 getBodyPos() const { return m_body->GetPosition(); }

    float getBodyMass() const { return m_body->GetMass(); }

    b2Vec2 getBodyLinearVelocity() const { return m_body->GetLinearVelocity(); };

    virtual Objects_t getBodyType() const = 0;

protected:
    b2Body *getBody() const { return m_body; }
    sf::Sprite & getSprite() { return m_sprite; }

private:
    b2Body *m_body;
    sf::Sprite m_sprite;
    b2World & m_world;
    sf::Vector2f m_pos;
    std::unique_ptr<Animation> m_animation;
};