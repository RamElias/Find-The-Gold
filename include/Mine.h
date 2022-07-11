#pragma once

#include "Macros.h"
#include "ResourceManager.h"
#include "box2d/box2d.h"
#include "Objects/movingObj/Player.h"
#include "Objects/movingObj/Enemy.h"
#include "Contact.h"
#include "Objects/staticObj/StaticObject.h"
#include "Objects/staticObj/gift/Gift.h"


class Mine 
{
public:
   
    Mine(const minePairIter& Mine, Textures_t backGround); 

    void build(const std::pair <mineIter, mineIter>&);

    int runMine(sf::RenderWindow& window);

    void displayInfo(sf::RenderWindow&);

    void drawInfo(sf::RenderWindow& window, const std::string& detail, int index);

    void createGift(sf::Vector2f pos);

    void draw(sf::RenderWindow& window, const sf::Time & deltaTime);
    
    void playSound(const bool play, int index);

private:
    void moveMovingObject(sf::RenderWindow &);

    void changeView(sf::RenderWindow & window);

    int checkStatus(sf::RenderWindow & window);

    void createsounds();

    void checkSound();

    int m_width;
    int m_height; 
    int m_demandCoins;

    b2World m_world;
    sf::Sprite m_backGround;
    std::vector<sf::Text> m_info;
    Contact m_contact;

    std::shared_ptr<Player> m_player;
    std::vector< std::shared_ptr<Enemy>> m_enemies;
    std::vector<std::vector<std::shared_ptr<StaticObject>>> m_staticObjects;
    std::vector <std::shared_ptr<Gift>> m_gifts;
    std::vector<sf::Sound> m_sounds;
};
