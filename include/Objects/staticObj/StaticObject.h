#pragma once

#include "Objects/GameObject.h"
#include "Factory.h"

//class that is incharge of all static object in the game
class StaticObject : public GameObject
{
public:
    StaticObject(const sf::Sprite &, const sf::Vector2f &, b2World &,
                 const sf::Vector2f&, const bool , b2BodyType, std::unique_ptr<Animation> = nullptr);

    void taken() { m_taken = true; }
    bool isTaken() { return m_taken; }

private:
    bool m_taken = false;
};