#include "Mine.h"

Mine::Mine(const minePairIter& Mine, Textures_t backGround)
    : m_world({0, 9.8}),
      m_backGround(ResourceManager::instance().getSprite(backGround))
{
    srand(time(NULL));
    m_info.resize(NUM_OF_INFO);
    m_world.SetContactListener(&m_contact);

    // Reads Mine sizes - Width, Height.
    auto stringStream = std::stringstream();

    stringStream << *Mine.first;
    stringStream >> m_width >> m_height >> m_demandCoins;
     
    m_backGround.scale(WINDOW_SIZE.first / m_backGround.getGlobalBounds().width,
                       WINDOW_SIZE.second / m_backGround.getGlobalBounds().height);

    build(Mine); 
}

//-----------------------------------------------
//build the mine and the objects
void Mine::build(const std::pair <mineIter, mineIter>& Mine) 
{   
    m_staticObjects.resize(m_height);

    size_t row = 0;

    //creates the sound for the game
    createsounds();

    //Creates mine objects
    for (auto iter = Mine.first + 1; iter < Mine.second; ++iter, ++row) 
    {
        for (size_t col = 0; col < iter->size(); ++col) 
        {
            auto object = (*iter)[col];
            switch (object) 
            {
                case PLAYER:
                    m_player = std::make_shared<Player>(sf::Vector2f(col, row), m_world, sf::Vector2f(m_width ,m_height));
                    break;

                case DINO_ENEMY:
                case ROBOT_ENEMY:
                    m_enemies.emplace_back(Factory<Enemy>::create(object, sf::Vector2f(col, row), m_world,
                        sf::Vector2f(m_width, m_height)));
                    break;

                case GIFT:
                    createGift(sf::Vector2f(col, row));
                    break;

                default:
                    auto staticObject = Factory<StaticObject>::create(object, sf::Vector2f(col, row),
                                                                      m_world, sf::Vector2f(m_width, m_height));
                   
                    if(!staticObject && object != ' ')
                        throw std::invalid_argument("Invalid character was entered in mines.txt file.");

                    m_staticObjects[row].emplace_back(staticObject);
            }
        }
    }
}

//-----------------------------------------------
//run the mine, return satus_t num(won,lost,continue)
int Mine::runMine(sf::RenderWindow& window)
{
    m_world.Step(TIME_STEP, VEL_ITERATIONS, POS_ITERATIONS);
    moveMovingObject(window);
    changeView(window);
    displayInfo(window);
    checkSound();

    return checkStatus(window);
}

//-----------------------------------------------
//function for the moves of the movind objects in the game
void Mine::moveMovingObject(sf::RenderWindow & window) {

    if (!m_player->isDead())
        m_player->move();
    
    else
    {
        auto clock = sf::Clock();
        auto animationTime = sf::Clock();
        m_player->setAnimationStatus(AnimationStatus_t::Death);
        //delay the death animation
        while (animationTime.getElapsedTime().asSeconds() <= 2)
        {
            window.clear();
            draw(window, clock.restart());
            window.display();
        }
        return;
    }

    //loop for moving all the enemies
    for (auto i = 0; i < m_enemies.size() ; i++) 
    {
        if (!m_enemies[i]->isDead())
            m_enemies[i]->move(m_player->getPos());
        else 
        {
            m_enemies[i]->setAnimationStatus(AnimationStatus_t::Death);
            m_enemies.erase(m_enemies.begin() + i);
            i--;
        }
    }
}

//-----------------------------------------
//change the view of the game acoording to the player position
void Mine::changeView(sf::RenderWindow & window)
{
    auto view = window.getView();
    auto position = sf::Vector2f();

    auto viewSize = sf::Vector2f(float(WINDOW_SIZE.first / m_width) * WIDTH_VIEW,
                                 (float(WINDOW_SIZE.second / m_height) * HEIGHT_VIEW));

    view.setSize(viewSize);

    if(m_player->getPos().x > WINDOW_SIZE.first - view.getSize().x / 2)
        position.x = WINDOW_SIZE.first - view.getSize().x / 2;

    else if(m_player->getPos().x < view.getSize().x / 2)
        position.x = view.getSize().x / 2;

    else
        position.x = m_player->getPos().x;

    if(m_player->getPos().y > WINDOW_SIZE.second - view.getSize().y / 2)
        position.y = WINDOW_SIZE.second - view.getSize().y / 2;

    else if(m_player->getPos().y < view.getSize().y / 2)
        position.y = view.getSize().y / 2;

    else
        position.y = m_player->getPos().y;

    view.setCenter(position);
    window.setView(view);
}

//-----------------------------------------------
//check the player status, return status_t num
int Mine::checkStatus(sf::RenderWindow & window)
{
    if (m_player->getHP() == 0)
    {
        m_player->setHP(100);
        m_player->decLives();

        //player lost
        if (m_player->isDead()) 
        {
            window.setFramerateLimit(5);
            moveMovingObject(window);
            return Status_t::Lost;
        }
    }

    //player won
    if (m_player->checkWon())
    {
        if(m_player->getCoins() == m_demandCoins)
            return Status_t::Won;
    }

    return Status_t::Continue;
}

//-----------------------------------------------
//draw the mine objects
void Mine::draw(sf::RenderWindow& window, const sf::Time & deltaTime) 
{
    window.draw(m_backGround);
    
    for (auto& enemy : m_enemies)
    {
        enemy->draw(window, deltaTime);
        enemy->update(deltaTime, sf::Vector2f(m_width, m_height));
    }
    
    for (auto& staticObjectLine : m_staticObjects) 
        for (auto i = 0; i < staticObjectLine.size(); i++)
            if (staticObjectLine[i])
            {
                if (staticObjectLine[i]->isTaken())
                {
                    staticObjectLine.erase(staticObjectLine.begin() + i);
                    i--;
                }
                else
                {
                    staticObjectLine[i]->draw(window);
                    staticObjectLine[i]->update(deltaTime, sf::Vector2f(m_width, m_height));
                }
            }


    for (auto i = 0; i < m_gifts.size(); i++)
    {
        if (m_gifts[i]->isTaken())
        {
            m_gifts.erase(m_gifts.begin() + i);
            i--;
        }
        else
        {
            m_gifts[i]->draw(window);
            m_gifts[i]->update(deltaTime, sf::Vector2f(m_width, m_height));
        }
    }

    m_player->draw(window, deltaTime);
    m_player->update(deltaTime, sf::Vector2f(m_width, m_height));
    displayInfo(window);
}

//-----------------------------------------------
//display the info on the game
void Mine::displayInfo(sf::RenderWindow& window)
{
    drawInfo(window, "Lives: " + std::to_string(m_player->getLives()), 0);
    drawInfo(window, "HP: " + std::to_string(m_player->getHP()), 1);
    drawInfo(window, "       Coins: " + std::to_string(m_player->getCoins()) + "/" + std::to_string(m_demandCoins), 2);
    drawInfo(window, "                       Bullets: " + std::to_string(m_player->getBullets()), 3);
}

//-----------------------------------------------
//draw any info on the screen
void Mine::drawInfo(sf::RenderWindow& window, const std::string& detail, int index)
{
    auto view = window.getView();
    auto viewPosX = view.getCenter().x - (view.getSize().x / 2);
    auto viewPosY = view.getCenter().y - (view.getSize().y / 2);

    m_info[index].setFont(ResourceManager::instance().getFont());
    m_info[index].setCharacterSize(TEXT_CHAR_SIZE);
    m_info[index].setFillColor(sf::Color(34, 153, 84));
    m_info[index].setOrigin(m_info[index].getGlobalBounds().width / 2,
                            m_info[index].getGlobalBounds().height / 2);
    m_info[index].setString(detail);
    
    m_info[index].setPosition(viewPosX + (index*(view.getSize().x/5)) + 40 , viewPosY + 10);

    window.draw(m_info[index]);
}

//-----------------------------------------------
//create the gifts randomaly
void Mine::createGift(sf::Vector2f pos) 
{
    auto random = rand() % 3;
    switch (random) 
    {
        case HP:
            m_gifts.emplace_back(Factory<Gift>::create(HP_GIFT, pos,
                m_world, sf::Vector2f(m_width, m_height)));
            break;
       case LIFE:
           m_gifts.emplace_back(Factory<Gift>::create(BULLET_GIFT, pos,
                m_world, sf::Vector2f(m_width, m_height)));
            break;
        case BULLETS:
            m_gifts.emplace_back(Factory<Gift>::create(LIFE_GIFT, pos,
                m_world, sf::Vector2f(m_width, m_height)));
            break;
    }
}

//-----------------------------------------------
//get the sounds from resource manager and save them in m_sound
void Mine::createsounds()
{
    std::vector<sf::Sound> sound(NUM_OF_SOUNDS);
    for (int i = 0; i < NUM_OF_SOUNDS; i++)
    {
        sound[i].setBuffer(*ResourceManager::instance().getSound(i));
    }
    m_sounds = sound;
}

//-----------------------------------------------
//check if sound need to play
void Mine::checkSound()
{
    if (!ResourceManager::instance().getMute()) //if the sound is not off from setting
    {
        playSound(m_player->isInjured(), (int)sounds::collision);
        playSound(m_player->isTakenObj(), (int)sounds::bonus);
        playSound(m_player->isShoot(), (int)sounds::playerShoot); 
        playSound(m_player->isJump(), (int)sounds::jump); 

        for (auto& enemy : m_enemies) 
        {
            playSound(enemy->isShoot(), (int)sounds::robotShoot); 
            playSound(enemy->isInjured(), (int)sounds::enemyInjured);
        }
    }
}

//-----------------------------------------
//play the sound
void Mine::playSound(const bool play, int index)
{
    if (play)
    {
        m_sounds[index].play();
        m_sounds[index].setVolume(5);
    }
}