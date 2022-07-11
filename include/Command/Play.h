#pragma once

#include "Macros.h"
#include "Command/Command.h"
#include "Menu.h"
#include "Controller.h"
#include "Command/Continue.h"
#include "ResourceManager.h"
#include "Mine.h"

class Play: public Command
{
public:
	Play(const int) ;
	void buildPause();
	void readMine(std::fstream& file);
	std::pair<mineIter, mineIter> getMine();
	bool execute(sf::RenderWindow&) override;

private:
	void buildMine();

	void readFile(const std::string& );

	void draw(sf::RenderWindow& window);

	void GameOver(sf::RenderWindow& window);

	bool GameWon(sf::RenderWindow& window);

	void displayScreen(sf::RenderWindow& window, Textures_t screen);

	int m_currMine;
	int m_currLevel;

	std::vector<std::vector<std::string>> m_board;
	std::vector<std::unique_ptr<Mine>> m_mine;
	sf::Clock m_clock;
	Menu m_pause;

};
