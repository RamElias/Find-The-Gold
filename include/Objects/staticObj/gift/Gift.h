#pragma once

#include "Objects/staticObj/StaticObject.h"

class Gift : public StaticObject{
public:
    Gift(const sf::Sprite&, const sf::Vector2f&, b2World&, const sf::Vector2f&, std::unique_ptr<Animation> = nullptr);

private:
    static bool m_registerIt;
};