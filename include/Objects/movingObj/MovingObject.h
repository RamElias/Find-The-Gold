#pragma once

#include "Objects/GameObject.h"

//class that is incharge of all moving object in the game
class MovingObject : public GameObject 
{
public:
    MovingObject(const sf::Sprite &, const sf::Vector2f &, b2World &,
                const sf::Vector2f &, std::unique_ptr<Animation> = nullptr);

    virtual void draw(sf::RenderWindow&, sf::Time);

    void moveX(float = 0);
    void moveY(float = 0);

    virtual Side_t opposite(enum Side_t side);

    int getHP() { return m_hp; }
    void decreaseHP(const int );
    void incHP();
    void setHP(const int hp) { m_hp = hp; }
    
    void setInjured() { m_injured = true; }
    bool isInjured();

    void setShoot() { m_shoot = true; }
    bool isShoot();

private:
    Side_t m_side = Side_t::RIGHT;
    int m_hp ;
    bool m_shoot = false;
    bool m_injured = false;

};
