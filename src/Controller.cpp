#include "Controller.h"

Controller::Controller() :
	m_window(sf::VideoMode(WINDOW_SIZE.first, WINDOW_SIZE.second), "Find The Gold"),
	m_menu(ResourceManager::instance().getSprite(Textures_t::MENU_BACKGROUND_T))
{
	m_window.setFramerateLimit(60);
}

//-----------------------------------------------
void Controller::run()
{
	//add the buttons
	m_menu.add("New Game", std::make_unique<Play>(0));
	m_menu.add("How To Play", std::make_unique<HowToPlay>(1));
	m_menu.add("Setting", std::make_unique<Setting>(2));
	m_menu.add("Quit", std::make_unique<Exit>(3));

	m_menu.activate(m_window);
}

