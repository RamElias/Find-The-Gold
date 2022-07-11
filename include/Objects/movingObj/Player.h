#pragma once

#include "ResourceManager.h"
#include "Objects/movingObj/MovingObject.h"
#include "Objects/movingObj/Enemy.h"
#include "Objects/staticObj/Coin.h"
#include "Objects/staticObj/Gate.h"
#include "Objects/staticObj/gift/HpGift.h"
#include "Objects/staticObj/gift/LifeGift.h"
#include "Objects/staticObj/gift/BulletGift.h"
#include "Attack.h"

class Player : public MovingObject 
{
public:
    Player(const sf::Vector2f & pos, b2World &, const sf::Vector2f &);

    void move();

    Objects_t getBodyType() const override { return PLAYER; }
    
    void draw(sf::RenderWindow &, sf::Time) override;

    void startContact(Enemy*);
    void startContact(Coin*);
    void startContact(HpGift* HpGift);
    void startContact(BulletGift* HpGift);
    void startContact(LifeGift* HpGift);
    void startContact(Bullet*);
    void startContact(Gate* gate);

    bool checkWon();

    int getCoins() { return m_coins; }
 
    int getLives();
    void decLives() { m_lives--; }
    void incLives() { m_lives++; }

    int getBullets() { return m_bullets; }
    void incBullets() { m_bullets += BULLETS_GIFT; }

    bool isDead();
    
    bool isTakenObj();
    bool isJump();

private:
    static bool m_registerIt;
    b2FixtureDef m_fix;
    Side_t m_side = Side_t::RIGHT;
    AnimationStatus_t m_movement = AnimationStatus_t::Idle;

    int m_lives;
    int m_coins;
    int m_bullets;

    bool m_won = false;
    bool m_takenObj = false;
    bool m_jump = false;

    Attack m_attack;
};
