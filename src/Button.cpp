#include "Button.h"

Button::Button(int pos, std::string text)
    : m_rect(sf::Vector2f(BUTTON_SIZE.first, BUTTON_SIZE.second)),
      m_buttonText(text, ResourceManager::instance().getFont())
{
    m_rect.setPosition(WINDOW_SIZE.first/2 - BUTTON_SIZE.first, BUTTON_SIZE.second + 100 + (pos*150) ); 
    m_rect.setFillColor(sf::Color::Transparent);
    m_rect.setOutlineColor(sf::Color::Transparent);

    m_buttonText.setCharacterSize(BUTTON_CHAR_SIZE);
    m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 2);
    m_buttonText.setPosition(getPosition().x + getGlobalBound().width / 2,
                             getPosition().y + getGlobalBound().height / 2 - BUTTON_DIMENTION / 3);
    m_buttonText.setFillColor(sf::Color::Black);
    m_buttonText.setOutlineColor(sf::Color::White);
    m_buttonText.setOutlineThickness(BUTTON_THICKNESS);
}

//-----------------------------------------------
void Button::setString(const std::string& str) 
{
    m_buttonText.setString(str);
}

//-----------------------------------------------
bool Button::isPressed(const sf::Vector2f& position) const
{
    if (m_buttonText.getGlobalBounds().contains(position))
        return true;
    return false;
}

//-----------------------------------------------
sf::Vector2f Button::getPosition() const 
{
    return m_rect.getPosition();
}

//-----------------------------------------------
sf::FloatRect Button::getGlobalBound() const 
{
    return m_rect.getGlobalBounds();
}

//-----------------------------------------------
bool Button::globalBound(sf::Vector2f loc)
{
    return m_buttonText.getGlobalBounds().contains(loc);
}

//-----------------------------------------------
void Button::setOutline(sf::Color color)
{
    m_buttonText.setOutlineColor(color);
}

//-----------------------------------------------
//draw the button
void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_buttonText);
}