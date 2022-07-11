#pragma once

#include "Command/Command.h"

class Exit : public Command 
{
public:
    Exit(const int position) : Command(position, "Exit") {}

    bool execute(sf::RenderWindow&) override { exit(EXIT_SUCCESS); };

private:
};