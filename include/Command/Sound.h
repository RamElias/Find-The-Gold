#pragma once

#include "Command/Command.h"

class Sound : public Command
{
public:
    Sound(const int position) : Command(position, "sound: ON") {}

    //set the music according to the current status
    bool execute(sf::RenderWindow&) override
    {
        if (!ResourceManager::instance().getMute()) //music is on
        {
            setButtonTitle("sound: OFF");
            //turn off music
            ResourceManager::instance().playBackRoundSound(false);
            ResourceManager::instance().setMute(true);
        }
        else
        {
            setButtonTitle("sound: ON");
            //turn on music
            ResourceManager::instance().playBackRoundSound(true);
            ResourceManager::instance().setMute(false);
        }
        return true;
    };

private:
};