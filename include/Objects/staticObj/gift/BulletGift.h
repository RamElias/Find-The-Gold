#pragma once

#include "Objects/staticObj/gift/Gift.h"

class BulletGift : public Gift {
public:
	BulletGift(const sf::Vector2f&, b2World&, const sf::Vector2f&);
	Objects_t getBodyType() const override { return BULLET_GIFT; }

private:
	static bool m_registerIt;

};

