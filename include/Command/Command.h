#pragma once

#include "Button.h"
#include "ResourceManager.h"

// An abstract class that responsible for command in the menu.
class Command 
{
public:
    Command(int pos, std::string text) : m_button(pos, text){}

    virtual bool execute(sf::RenderWindow &) = 0;
    bool isPressed(sf::Vector2f position) const { return m_button.isPressed(position); }
    void setButtonTitle(const std::string & title) { m_button.setString(title); }
    void draw(sf::RenderWindow & window) const { m_button.draw(window); }
    void setOutline(sf::Color color) { m_button.setOutline(color); }

private:
    Button m_button;
};