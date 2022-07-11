#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <sstream>
#include <fstream>
#include <unordered_map>


using mineIter = std::vector<std::string>::const_iterator;
using minePairIter = std::pair<mineIter, mineIter>;

struct AnimationData
{
    using ListType = std::vector<sf::IntRect>;
    using DataType = std::unordered_map<enum class AnimationStatus_t, ListType>;
    DataType m_data;
};

//--------------------window details--------------------
const std::pair<int, int> WINDOW_SIZE = { 1920, 1080 };

const int WIDTH_VIEW = 12;
const int HEIGHT_VIEW = 8;
const int SCREEN_DELAY_TIME = 3;

//--------------------resources--------------------------
const int NUM_OF_TEXTURES = 18;
const int NUM_OF_ANIMATION = 10;
const int NUM_OF_SOUNDS = 9;
const auto ANIMATION_TIME = sf::seconds(0.1f);

//--------------------Menu and Buttons----------------
const int NUM_OF_INFO = 4;
const int NO_PRESSED = -1;
const std::pair<int, int> BUTTON_SIZE = { 100,200 };
const int BUTTON_CHAR_SIZE = 70;
const int BUTTON_DIMENTION = 25;
const int BUTTON_THICKNESS = 7;
const int TEXT_CHAR_SIZE = 14;

//--------------------Objects---------------------

const float VELOCITY = 5.0f;
const float PHYSICAL_SIZE = 0.48f;
const float TIME_STEP = 1.0f / 60.0f;
const int VEL_ITERATIONS = 6;
const int POS_ITERATIONS = 2;
const int ENEMY_VELOCITY = 2;
const int PLAYER_ENEMY_RANGE = 10;
const int CONTACT_AMOUNT = 5;
const float BULLET_DISTANCE = 0.7f;
const sf::Vector2f ANTI_GRAVITY(0, -0.15f);
const int BULLET_VELOCITY = 7;
const int BULLETS_GIFT = 15;
const float FIRE_RATE = 0.3f;
const float ROBOT_FIRE_RATE = 0.6f;
const float BULLET_DAMAGE = 25.f;
const float ENEMY_BULLET_DAMAGE = 20.f;
const int SHOOTING_RANGE = 300;
const int ENEMY_SHOOTING_RANGE = 150 ;
const float ENEMY_HIT = 9;
const int NUM_OF_LIVES = 3;
const int NUM_OF_BULLETS = 30;
const int MAX_HP = 100;

//----------------Enums-----------------
enum class Textures_t 
{
    MENU_BACKGROUND_T,
    HOW_TO_PLAY_T,
    NEXT_LEVEL_T,
    GAME_OVER_T,
    WON_T,
    MINE_BACKGROUND1_T,
    PLAYER_T,
    DINO_ENEMY_T,
    ROBOT_ENEMY_T,
    WALL_T,
    FLOOR_T,
    COIN_T,
    BULLET_T,
    WAGON_T,
    GATE_T,
    HP_GIFT_T,
    BULLET_GIFT_T,
    LIFE_GIFT_T
};

enum class AnimationStatus_t 
{
    Idle,
    Walk,
    Jump,
    Fall,
    Shoot,
    Hurt,
    Death,
    Round
};

enum ObjectsData_t 
{
    PLAYER_D,
    DINO_ENEMY_D,
    ROBOT_ENEMY_D,
    COIN_D,
    HP_GIFT_D,
    LIFE_GIFT_D,
    AMMO_GIFT_D
};

enum Objects_t 
{
    PLAYER = 'P',
    DINO_ENEMY = 'D',
    ROBOT_ENEMY = 'R',
    WALL = '#',
    FLOOR = '_',
    COIN = '$',
    BULLET = '*',
    WAGON = 'W',
    GATE = '@',
    GIFT = 'G',
    HP_GIFT = '1',
    BULLET_GIFT = '2',
    LIFE_GIFT = '3'
};

enum Gift_t
{
    HP,
    LIFE,
    BULLETS
};

enum class Side_t
{
    RIGHT,
    LEFT
};

enum Shape_t 
{
    CIRCLE_SHAPE,
    POLYGON_SHAPE
};

enum Status_t {
    Continue,
    Won,
    Lost
};

const enum class sounds
{
    background,
    collision,
    win,
    bonus,
    playerShoot,
    robotShoot,
    jump,
    enemyInjured,
    lost
};
