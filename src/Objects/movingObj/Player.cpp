#include "Objects/movingObj/Player.h"

//-----------------------------------------------
Player::Player(const sf::Vector2f & pos, b2World & world, const sf::Vector2f & dimension) 
    :MovingObject(ResourceManager::instance().getSprite(Textures_t::PLAYER_T), pos, world,dimension,
        std::make_unique<Animation>(ResourceManager::instance().animationData(PLAYER_D),
            AnimationStatus_t::Idle, getSprite(), dimension)),
        m_lives(NUM_OF_LIVES), m_attack(dimension, -2), m_coins(0), m_bullets(NUM_OF_BULLETS)
{
    b2Vec2 position(pos.x, pos.y);

    rigidBody(world, position, CIRCLE_SHAPE, PHYSICAL_SIZE, 2.f, 0.f, -2, 0, false, b2_dynamicBody);

    setUserData();

    setFixedRotation(true);
}

//-----------------------------------------------
// player move by clicks
void Player::move() 
{
    // player movment - jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
        && m_movement != AnimationStatus_t::Jump 
        && m_movement != AnimationStatus_t::Fall 
        && m_movement != AnimationStatus_t::Shoot)
    {
        moveY(-VELOCITY);
        m_jump = true;
    }
    
    // player movment - walk to the left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
             || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
        moveX(-VELOCITY);
        m_side = opposite(Side_t::LEFT);
    }

    // player movment - walk to the right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) 
             || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
        moveX(VELOCITY);
        m_side = opposite(Side_t::RIGHT);
    }

    // player movment - dont move
    else 
    {
        moveX(0);
        m_movement = AnimationStatus_t::Idle;
    }

    // player movment - shoting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) 
    {
        m_movement = AnimationStatus_t::Shoot;
        
        if (m_bullets > 0)
        {
            if (m_attack.shoot(getPos(), *getBody()->GetWorld(), m_side))
            {
                setShoot();
                m_bullets--;
            }
        }
    }

    // sets the player sprite  to the physical world.
    if (getBody()->GetLinearVelocity().y < 0)
        m_movement = AnimationStatus_t::Jump;

    else if (getBody()->GetLinearVelocity().y > 0)
        m_movement = AnimationStatus_t::Fall;

    else if (getBody()->GetLinearVelocity().x != 0)
        m_movement = AnimationStatus_t::Walk;

    else if (m_movement != AnimationStatus_t::Shoot)
            m_movement = AnimationStatus_t::Idle;
    
    m_attack.bulletCheck(); // if bullet was fired
    setAnimationStatus(m_movement);//set the animation
}


//-----------------------------------------------
void Player::draw(sf::RenderWindow & window, sf::Time deltaTime)
{
    MovingObject::draw(window,deltaTime);
    m_attack.drawBullet(window, deltaTime);
}


//-----------------------------------------------
void Player::startContact(Enemy* enemy)
{
    if (enemy->getMovement() == AnimationStatus_t::Death)
        return;
    
    decreaseHP(CONTACT_AMOUNT);

    setInjured();
}

//-----------------------------------------------
void Player::startContact(Coin* coin)
{
    m_coins++;
    coin->taken();
    //m_won = true;
    m_takenObj = true;
}

//-----------------------------------------------
void Player::startContact(HpGift* HpGift)
{
    HpGift->taken();
    incHP();
    m_takenObj = true;
}

//-----------------------------------------------
void Player::startContact(BulletGift* BulletGift)
{
    BulletGift->taken();
    incBullets();
    m_takenObj = true;
}

//-----------------------------------------------
void Player::startContact(LifeGift* LifeGift)
{
    LifeGift->taken();
    incLives();
    m_takenObj = true;
}

//-----------------------------------------------
void Player::startContact(Bullet* bullet) 
{
    decreaseHP(bullet->getHit());
    bullet->hit();
    setInjured();
}

//-----------------------------------------------
void Player::startContact(Gate* gate) 
{
    m_won = true;
}

//-----------------------------------------------
bool Player::checkWon()
{
    auto temp = m_won;
    m_won = false;
    return temp;
}

//-----------------------------------------------
int Player::getLives()
{
    if (m_lives < 0)
        return 0;
    return m_lives;
}

//-----------------------------------------------
bool Player::isDead()
{
    if (m_lives < 0)
    {
        setHP(0);
        return true;
    }
    return false;
}

//-----------------------------------------------
bool Player::isTakenObj()
{
    auto temp = m_takenObj;
    m_takenObj = false;
    return temp;
}


//-----------------------------------------------
bool Player::isJump()
{
    auto temp = m_jump;
    m_jump = false;
    return temp;
}
