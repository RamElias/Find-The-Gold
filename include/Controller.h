#pragma once
#include "Macros.h"
#include "ResourceManager.h"
#include "Menu.h"
#include "Command/Play.h"
#include "Command/HowToPlay.h"
#include "Command/Setting.h"
#include "Command/Exit.h"

class Controller
{
public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	Menu m_menu;
};
