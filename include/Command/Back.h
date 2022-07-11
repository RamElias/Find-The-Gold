
#pragma once


#include "Command/Command.h"

class Back : public Command
{
public:
    Back(const int position) : Command(position, "Back") {}

    bool execute(sf::RenderWindow&) override { return false; };

private:
};