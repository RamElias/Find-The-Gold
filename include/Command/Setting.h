#pragma once

#include "Menu.h"

#include "Command\Sound.h"
#include "Command\Back.h"

class Setting : public Command 
{
public:
    Setting(const int position) : Command(position, "Setting"),
                                        m_setting(ResourceManager::instance().getSprite(Textures_t::MENU_BACKGROUND_T))
    {
        //make the menu of setting
        m_setting.add("Sound", std::make_unique<Sound>(1));
        m_setting.add("Back", std::make_unique<Back>(2));
    }

    //run the menu of setting
    bool execute(sf::RenderWindow& window)
    {
        m_setting.activate(window);
        return true;
    }

private:
    Menu m_setting;
};