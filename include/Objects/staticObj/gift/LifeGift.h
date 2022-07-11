#pragma once

#include "Objects/staticObj/gift/Gift.h"

// A class that implements a gift of hp.

class LifeGift : public Gift 
{
public:
	LifeGift(const sf::Vector2f&, b2World&, const sf::Vector2f&);

	Objects_t getBodyType() const override { return LIFE_GIFT; }

private:
	static bool m_registerIt;
};

