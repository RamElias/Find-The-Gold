#pragma once

#include "Command/Command.h"

class Continue : public Command
{
public:
    Continue(const int position) : Command(position, "Continue") {}

    bool execute(sf::RenderWindow&) override { return false; };

private:
};