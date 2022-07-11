#pragma once

#include "Macros.h"
#include "ResourceManager.h"

// A class that responsible for animation
class Animation
{
public:
    Animation(const AnimationData & data, AnimationStatus_t, sf::Sprite &, const sf::Vector2f &);

    void setStatus(AnimationStatus_t);

    void update(sf::Time);

private:
    void update();

    int m_index = 0;
    sf::Sprite& m_sprite;
    sf::Time m_elapsed = {};
    sf::Vector2f m_dimension;
    const AnimationData& m_data;
    AnimationStatus_t m_status = AnimationStatus_t::Idle;
};
