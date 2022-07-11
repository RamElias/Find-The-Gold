#pragma once

#include "Objects/movingObj/Bullet.h"

// A class that responsible for attack action
class Attack 
{
public:
	Attack(const sf::Vector2f &,const int);

	bool shoot(sf::Vector2f, b2World &, Side_t = Side_t::RIGHT);
	void setFireRate(const float &);
    void setBulletVelocity(const float &);
	void setBulletDamage(const float&);
	void bulletCheck();
	void drawBullet(sf::RenderWindow&, sf::Time);

private:
	int m_hit;
	sf::Vector2f m_dimension;
	sf::Clock m_clock;
	float m_bulletDamage;
	float m_fireRate;
    float m_bulletVelocity = BULLET_VELOCITY;
	std::vector<std::unique_ptr<Bullet>> m_bullets;
};