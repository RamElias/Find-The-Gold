#pragma once

#include "Macros.h"
#include "Command/Command.h"
#include "Button.h"

class Menu 
{
public:
    Menu(const sf::Sprite&);

    void add(const std::string&, std::unique_ptr<Command>);

    void activate(sf::RenderWindow& window);

private:
    int getCommand(sf::RenderWindow& window);

    bool performAction(sf::RenderWindow& window, int option);

    void draw(sf::RenderWindow&);

    int handleClick(sf::Vector2f position);

    void handleMouseMove(sf::RenderWindow& window, const sf::Vector2f& location);

    typedef std::pair<std::string, std::unique_ptr<Command>> Button_type;
    std::vector<Button_type> m_buttons; 
    sf::Sprite m_backGround;
};