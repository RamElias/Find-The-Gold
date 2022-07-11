#include "Menu.h"

Menu::Menu(const sf::Sprite& backGround) : m_backGround(backGround)
{
    m_backGround.setScale(WINDOW_SIZE.first / m_backGround.getGlobalBounds().width,
        WINDOW_SIZE.second / m_backGround.getGlobalBounds().height);

    //play the background music
    ResourceManager::instance().playBackRoundSound(true);
}

//-----------------------------------------------
void Menu::add(const std::string& name, std::unique_ptr<Command> command) 
{
    m_buttons.emplace_back(Button_type(name, std::move(command)));
}

//-----------------------------------------------
//run the menu
void Menu::activate(sf::RenderWindow& window) 
{
    int command;
    do 
    {
        draw(window);
        command = getCommand(window);
    }
    while (performAction(window, command));
}

//-----------------------------------------------
//handle the events and return the command number
int Menu::getCommand(sf::RenderWindow& window) 
{
    while (true) 
    {
        draw(window);
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            switch (event.type) 
            {
            case sf::Event::Closed:
                window.close();
                exit(EXIT_SUCCESS);

            case sf::Event::MouseMoved:
                handleMouseMove(window, window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Button::Left) 
                {
                    return handleClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
                }
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Escape) 
                {
                    if (m_buttons[0].first == "Continue") //in pause menu
                        return 0;
                    return (m_buttons.size() - 1);
                }
                break;
            }
        }
    }
    return false;
}

//-----------------------------------------------
//execute the command
bool Menu::performAction(sf::RenderWindow& window, int button)
{
    if (button == NO_PRESSED)
        return true;
    return m_buttons[button].second->execute(window);
}

//-----------------------------------------------
//draw the menu
void Menu::draw(sf::RenderWindow& window)
{
    window.clear();
    window.draw(m_backGround);

    for (auto& button : m_buttons)
    {
       button.second->draw(window);
    }

    window.display();
}

//-----------------------------------------------
//return the button number that was pressed
int Menu::handleClick(sf::Vector2f position) 
{
    for (int button = 0; button < m_buttons.size(); ++button)
        if (m_buttons[button].second->isPressed(position)) 
            return button;
    return NO_PRESSED;
}

//-----------------------------------------------
//mark the button that the mouse is on
void Menu::handleMouseMove(sf::RenderWindow& window, const sf::Vector2f& location)
{
    for (auto i = 0; i < m_buttons.size(); ++i)
    {
        if (m_buttons[i].second->isPressed(location))
            m_buttons[i].second->setOutline(sf::Color::Red);
        
        else
            m_buttons[i].second->setOutline(sf::Color::White);
    }
}