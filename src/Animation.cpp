#include "Animation.h"

Animation::Animation(const AnimationData & data, AnimationStatus_t status,
                    sf::Sprite & sprite,const sf::Vector2f & dimension) 
    :m_data(data), m_status(status), m_sprite(sprite), m_dimension(dimension)
{
    update();
}

//-----------------------------------------------
//set the animation status
void Animation::setStatus(AnimationStatus_t status)
{
    if (m_status != status)
        m_index = 0;
    m_status = status;
    update();
}

//-----------------------------------------------
// updates the index of the sprite sheet.
void Animation::update(sf::Time delta)
{
    m_elapsed += delta;

    if (m_elapsed >= ANIMATION_TIME)
    {
        m_elapsed -= ANIMATION_TIME;
        ++m_index;

        //prevent a loop of the animation.
        if(m_status == AnimationStatus_t::Jump 
           || m_status == AnimationStatus_t::Fall 
           || m_status == AnimationStatus_t::Death)
        {
            if(m_index == m_data.m_data.find(m_status)->second.size())
                --m_index;
        }
        else
            m_index %= m_data.m_data.find(m_status)->second.size();
        
        update();
    }
}

//-----------------------------------------
// updates the sprite of the animation.
void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_status)->second[m_index]);

    auto scale = m_sprite.getScale().x;

    // Scale the sprite
    m_sprite.setScale(WINDOW_SIZE.first / (m_sprite.getLocalBounds().width * m_dimension.x),
                      WINDOW_SIZE.second / (m_sprite.getLocalBounds().height * m_dimension.y));
    if(scale < 0)
        m_sprite.scale(-1,1);

    //set origin to the sprite center
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}