#pragma once

#include "Command/Command.h"

class HowToPlay : public Command
{
public:

    HowToPlay(const int position) : Command( position , "How to play") {}

    //-----------------------------------------------
    //shows how to play screen
    bool execute(sf::RenderWindow& window) override 
    {
       auto background =  ResourceManager::instance().getSprite(Textures_t::HOW_TO_PLAY_T);

       background.setScale(WINDOW_SIZE.first / background.getGlobalBounds().width,
           WINDOW_SIZE.second / background.getGlobalBounds().height);

       while (window.isOpen())
       {
           window.clear();

           window.draw(background);

           window.display();

           for (auto event = sf::Event{}; window.pollEvent(event);)
           {
               switch (event.type)
               {
               case sf::Event::Closed:
                   window.close();
                   exit(EXIT_SUCCESS);

               case sf::Event::MouseButtonPressed:
                   
               case sf::Event::KeyReleased:
                   return true;
               }
           }
       }

    };

private:

};