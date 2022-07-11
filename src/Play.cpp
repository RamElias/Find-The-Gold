#include "Command/Play.h"

Play::Play(const int position) :
    Command(position, "New Game"),
    m_currMine(0), m_currLevel(0),
    m_pause(ResourceManager::instance().getSprite(Textures_t::MENU_BACKGROUND_T))
{
    buildPause();
    buildMine();
}

//-----------------------------------------------
//build the pause menu
void Play::buildPause()
{
    m_pause.add("Continue", std::make_unique<class Continue>(0));
    m_pause.add("How To Play", std::make_unique<HowToPlay>(1));
    m_pause.add("Settings", std::make_unique<Setting>(2));
    m_pause.add("Exit", std::make_unique<Exit>(3));
}

//-----------------------------------------------
//build the mines levels and insert them to m_mine
void Play::buildMine() 
{
    readFile("mines.txt");

    //Creates the levels (each level is mine) of the game
    while (m_currMine != m_board.size())
    {
        auto mineDec = getMine();
        m_mine.emplace_back(std::make_unique<Mine>(mineDec, Textures_t::MINE_BACKGROUND1_T));
        ++m_currMine;
    }
    m_currMine = 0;
}

//-----------------------------------------------
//read the levels file
void Play::readFile(const std::string& fileName)
{
    auto mineFile = std::fstream(fileName);

    int numOfMines;

    //read the num of mines
    mineFile >> numOfMines;
    mineFile.get();

    m_board.resize(numOfMines);
  
    for (auto i = 0; i < numOfMines; ++i, ++m_currMine)
        readMine(mineFile);
    
    m_currMine = 0;
}

//-----------------------------------------------
//read a single level
void Play::readMine(std::fstream& file) 
{
    int Width, Height;
    auto stringStream = std::stringstream();
    auto line = std::string();

    // Reads the size of the Mine.
    std::getline(file, line);
    stringStream << line;

    stringStream >> Width >> Height;

    m_board[m_currMine].emplace_back(line);

    for (auto i = 0; i < Height; ++i)
    {
        std::getline(file, line);

        m_board[m_currMine].emplace_back(line);
    }
}

//-----------------------------------------------
//return pair of iterators(begin,end) from m_board of the current mine
std::pair <mineIter, mineIter> Play::getMine()
{
    auto begin = m_board[m_currMine].cbegin();
    auto end = m_board[m_currMine].cend();

    auto mine = std::make_pair(begin, end);

    return mine;
}

//-----------------------------------------------
//run the game events
bool Play::execute(sf::RenderWindow& window)
{    
    m_clock.restart();

    while (window.isOpen()) 
    {
        window.clear();

        switch (m_mine[m_currMine]->runMine(window)) //get the game status
        {
        case Status_t::Lost:
            GameOver(window);
            return true;

        case Status_t::Won:
            if (GameWon(window))
                return true;
            else
                break;

        case Status_t::Continue:
            draw(window);
            for (auto event = sf::Event{}; window.pollEvent(event);)
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    exit(EXIT_SUCCESS);

                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window.setView(window.getDefaultView());
                        m_pause.activate(window);
                        break;
                    }
                }
            }
        }
        window.display();
    }
    return true;
}

//-----------------------------------------------
void Play::draw(sf::RenderWindow& window)
{
    m_mine[m_currMine]->draw(window, m_clock.restart());
}

//-----------------------------------------
//handle player lost to enemies and restart the levels
void Play::GameOver(sf::RenderWindow& window)
{
    window.setFramerateLimit(60);
    window.setView(window.getDefaultView());
    m_mine[m_currMine]->playSound(!ResourceManager::instance().getMute(), (int)sounds::lost);

    //shows lost screen
    displayScreen(window, Textures_t::GAME_OVER_T);

    //restart the levels
    m_currMine = 0;
    m_mine.clear();
    m_board.clear();
    buildMine();
    m_currMine = m_currLevel;
}

//-----------------------------------------------
//handle player finish the level 
bool Play::GameWon(sf::RenderWindow& window)
{
    window.setFramerateLimit(60);
    window.setView(window.getDefaultView());
    m_mine[m_currMine]->playSound(!ResourceManager::instance().getMute(), (int)sounds::win);
    
    //if it is not the last level
    if (m_currMine != m_mine.size()-1)
    {
        m_currMine++;
        m_currLevel++;
        displayScreen(window, Textures_t::NEXT_LEVEL_T); //for next level massage
        return false;
    }
    else
    {
        m_currMine = 0; 
        m_currLevel = 0;
        displayScreen(window, Textures_t::WON_T); //for end game massage
        //resatrt the levels
        m_mine.clear();
        m_board.clear();
        buildMine();

        return true;
    }
}

//-----------------------------------------------
void Play::displayScreen(sf::RenderWindow& window, Textures_t screen) 
{
    auto sprite = ResourceManager::instance().getSprite(screen);
    sprite.setScale(WINDOW_SIZE.first / sprite.getGlobalBounds().width,
                    WINDOW_SIZE.second / sprite.getGlobalBounds().height);
    window.clear();
    window.draw(sprite);
    window.display();
    
    sf::sleep(sf::seconds(SCREEN_DELAY_TIME)); //delay the screen show for SCREEN_DELAY_TIME seconds
}

