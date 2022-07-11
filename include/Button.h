#pragma once
#include "Macros.h"
#include "ResourceManager.h"

class Button 
{
public:
    Button(int pos, std::string text);
    void setString(const std::string& str);
    bool isPressed(const sf::Vector2f&) const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBound() const;
    bool globalBound(sf::Vector2f loc);
    void setOutline(sf::Color color);
    bool doButton(sf::RenderWindow&) { return false; }
    
    void draw(sf::RenderWindow& ) const;

private:
    sf::RectangleShape m_rect;
    sf::Text m_buttonText;
};

