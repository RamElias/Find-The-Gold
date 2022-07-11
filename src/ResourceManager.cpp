#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{}

//-----------------------------------------------
//gets the resource, using static for one time loading the files
ResourceManager& ResourceManager::instance()
{
    static auto resource = ResourceManager();
    return resource;
}

//-----------------------------------------------
//constartoe that loads the font, textures and sounds
ResourceManager::ResourceManager()
{
    m_textures.resize(NUM_OF_TEXTURES);
    m_animationsData.resize(NUM_OF_ANIMATION);
    
    loadFont("CrispyTofu.ttf");

    //Textures load
    loadTexture(Textures_t::MENU_BACKGROUND_T, "MenuBackground.png");
    loadTexture(Textures_t::HOW_TO_PLAY_T, "howtoplay.png");
    loadTexture(Textures_t::NEXT_LEVEL_T, "nextLevel.png");
    loadTexture(Textures_t::GAME_OVER_T, "lostBG.png");
    loadTexture(Textures_t::WON_T, "wonBG.png");
    loadTexture(Textures_t::MINE_BACKGROUND1_T, "BackGround.jpg");
    loadTexture(Textures_t::PLAYER_T, "player.png");
    loadTexture(Textures_t::DINO_ENEMY_T, "dinoEnemy.png");
    loadTexture(Textures_t::ROBOT_ENEMY_T, "robotEnemy.png");
    loadTexture(Textures_t::FLOOR_T, "floor.png");
    loadTexture(Textures_t::WALL_T, "wall.png");
    loadTexture(Textures_t::COIN_T, "coin.png");
    loadTexture(Textures_t::BULLET_T, "bullet.png");
    loadTexture(Textures_t::WAGON_T, "wagon.png");
    loadTexture(Textures_t::GATE_T, "gate.png");
    loadTexture(Textures_t::HP_GIFT_T, "hp.png");
    loadTexture(Textures_t::LIFE_GIFT_T, "heart.png");
    loadTexture(Textures_t::BULLET_GIFT_T, "ammo.png");

    //create animation
    m_animationsData[PLAYER_D] = playerData();
    m_animationsData[DINO_ENEMY_D] = dinoEnemyData();
    m_animationsData[ROBOT_ENEMY_D] = robotEnemyData();
    m_animationsData[COIN_D] = coinData();
    m_animationsData[HP_GIFT_D] = hpGiftData();
    m_animationsData[LIFE_GIFT_D] = lifeGiftData();
    m_animationsData[AMMO_GIFT_D] = ammoGiftData();

    createSound();
}

//-----------------------------------------------
//function that loads the sounds of the game
void ResourceManager::createSound()
{
    m_soundVec.resize(NUM_OF_SOUNDS);
    loadSound(sounds::background, "backgroundMusic.ogg");
    loadSound(sounds::collision, "strikeSound.wav");
    loadSound(sounds::win, "winSound.wav");
    loadSound(sounds::bonus, "bonusSound.wav");
    loadSound(sounds::playerShoot, "playerShoot.wav");
    loadSound(sounds::robotShoot, "robotShoot.wav");
    loadSound(sounds::jump, "jumpSound.wav");
    loadSound(sounds::enemyInjured, "enemyInjuredSound.wav");
    loadSound(sounds::lost, "lostSound.wav");

    m_BackRoundsound.setBuffer(m_soundVec[0]);
    m_BackRoundsound.setVolume(2);
}

//-----------------------------------------------
//function that get index and return a sound from the sound vector
sf::SoundBuffer* ResourceManager::getSound(const int record)
{
    return &this->m_soundVec[record];
}

//-----------------------------------------------
//function that loads the sounds from the buffer to the m_sound
void ResourceManager::loadSoundFromBuffer()
{
    std::vector<sf::Sound> sound(m_soundVec.size());
    for (int i = 0; i < m_soundVec.size(); i++)
    {
        sound[i].setBuffer(m_soundVec[i]);
    }
    m_sound = sound;
}

//-----------------------------------------------
std::vector<sf::Sound> ResourceManager::getSoundVec()
{
    return m_sound;
}

//-----------------------------------------------
bool ResourceManager::getMute()
{
    return m_mute;
}

//-----------------------------------------------
void ResourceManager::setMute(bool stat)
{
    m_mute = stat;
}

//-----------------------------------------------
//play the backgtound music
void ResourceManager::playBackRoundSound(const bool play)
{
    if (play)
        m_BackRoundsound.play();
    else
        m_BackRoundsound.stop();
}

//-----------------------------------------------
void ResourceManager::loadTexture(Textures_t pos, const std::string& name)
{
    if (!m_textures[int(pos)].loadFromFile(name)) 
    {
        throw std::runtime_error(name + " is missing");
    }
}

//-----------------------------------------------
void ResourceManager::loadSound(sounds pos, const std::string& name)
{
    if (!m_soundVec[int(pos)].loadFromFile(name))
    {
        throw std::runtime_error(name + " is missing");
    }
}

//-----------------------------------------------
void ResourceManager::loadFont(const std::string& name)
{
    if (!m_font.loadFromFile(name))
    {
        throw std::runtime_error(name + " is missing");
    }
}

//-----------------------------------------------
const sf::Font& ResourceManager::getFont() const
{
    return m_font;
}

//-----------------------------------------------
//functions for create the sprites to the animation 
AnimationData ResourceManager::playerData() 
{
    auto player = AnimationData{};
    
    player.m_data[AnimationStatus_t::Idle].emplace_back(240, 175, 470, 492);

    player.m_data[AnimationStatus_t::Walk].emplace_back(209,  960,  450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(826,  960,  450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(1454, 960, 450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(2064, 960, 450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(2764, 960, 450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(3380, 960, 450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(4015, 960, 450, 492);
    player.m_data[AnimationStatus_t::Walk].emplace_back(4662, 960, 450, 492);

    player.m_data[AnimationStatus_t::Jump].emplace_back(225, 1747,  490, 505);
    player.m_data[AnimationStatus_t::Jump].emplace_back(855, 1747,  490, 505);
    player.m_data[AnimationStatus_t::Jump].emplace_back(1470, 1747, 490, 505);
    player.m_data[AnimationStatus_t::Jump].emplace_back(2110, 1747, 490, 505);
    player.m_data[AnimationStatus_t::Jump].emplace_back(2750, 1747, 490, 505);
    player.m_data[AnimationStatus_t::Jump].emplace_back(3390, 1747, 490, 505);
    
    player.m_data[AnimationStatus_t::Fall].emplace_back(4030, 1747, 530, 505);
    player.m_data[AnimationStatus_t::Fall].emplace_back(4670, 1747, 530, 505);
    player.m_data[AnimationStatus_t::Fall].emplace_back(5310, 1747, 530, 505);
    player.m_data[AnimationStatus_t::Fall].emplace_back(5950, 1747, 530, 505);

    player.m_data[AnimationStatus_t::Shoot].emplace_back(255, 2505, 530, 505); 
    player.m_data[AnimationStatus_t::Shoot].emplace_back(900, 2505, 530, 505);
    player.m_data[AnimationStatus_t::Shoot].emplace_back(1540, 2505, 530, 505);

    player.m_data[AnimationStatus_t::Death].emplace_back(305, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(935, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(1544, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(2158,  3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(2771, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(3366, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(3963,  3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(4569, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(5173, 3892, 502, 475);
    player.m_data[AnimationStatus_t::Death].emplace_back(5778, 3892, 502, 475);


    return player;
}

//-----------------------------------------------
AnimationData ResourceManager::dinoEnemyData()
{
    auto DinoEnemyData = AnimationData{};

    DinoEnemyData.m_data[AnimationStatus_t::Idle].emplace_back(913, 240, 365, 388);

    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(197,  2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(885,  2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(1567, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(2253, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(2934, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(3600, 2158, 355, 424);   
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(4287, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(4974, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(5653, 2158, 355, 424);
    DinoEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(6325, 2158, 355, 424);

    DinoEnemyData.m_data[AnimationStatus_t::Hurt].emplace_back(885, 2158, 355, 424);

    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(505,  3016, 405, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(949,  3055, 418, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(1672, 2960, 428, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(2358, 2960, 488, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(3019, 2947, 556, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(3703, 2947, 550, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(4383, 2947, 550, 440);
    DinoEnemyData.m_data[AnimationStatus_t::Death].emplace_back(5064, 2947, 550, 440);

    return DinoEnemyData;
}

//-----------------------------------------------
AnimationData ResourceManager::robotEnemyData()
{
    auto RobotEnemyData = AnimationData{};

    RobotEnemyData.m_data[AnimationStatus_t::Idle].emplace_back(90, 1474, 400, 464);
   
    RobotEnemyData.m_data[AnimationStatus_t::Hurt].emplace_back(642, 814, 400, 464);

    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(103,  814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(642,  814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(1200, 814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(1752, 814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(2355, 814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(2898, 814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(3434, 814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(4051 ,814, 400, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Walk].emplace_back(4615 ,814, 400, 464);

    RobotEnemyData.m_data[AnimationStatus_t::Shoot].emplace_back(4615 ,814, 400, 464);

    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(97,   147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(657,  147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(1227, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(1777, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(2325, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(2883, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(3464, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(4030, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(4592, 147, 507, 464);
    RobotEnemyData.m_data[AnimationStatus_t::Death].emplace_back(5154, 147, 507, 464);

    return RobotEnemyData;
}

//-----------------------------------------------
AnimationData ResourceManager::coinData()
{
    auto coin  = AnimationData{};

    coin.m_data[AnimationStatus_t::Round].emplace_back(0, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(0, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(90 ,0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(90, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(180 ,0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(180, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(250 ,0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(250, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(330  ,0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(330, 0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(420 ,0, 85, 85);
    coin.m_data[AnimationStatus_t::Round].emplace_back(420, 0, 85, 85);

    return coin;
}

//-----------------------------------------------
AnimationData ResourceManager::hpGiftData()
{
    auto hp = AnimationData{};

    hp.m_data[AnimationStatus_t::Round].emplace_back(47, 50, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(47, 50, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(47, 50, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(458, 44, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(458, 44, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(458, 44, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(834 ,44, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(834, 44, 257, 255);
    hp.m_data[AnimationStatus_t::Round].emplace_back(834, 44, 257, 255);

    return hp;
}

//-----------------------------------------------
AnimationData ResourceManager::lifeGiftData()
{
    auto life = AnimationData{};

    life.m_data[AnimationStatus_t::Round].emplace_back(357, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(357, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(357, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(270, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(270, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(270, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(184, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(184, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(184, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(97, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(97, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(97, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(10, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(10, 21, 72, 65);
    life.m_data[AnimationStatus_t::Round].emplace_back(10, 21, 72, 65);

    return life;
}

//-----------------------------------------------
AnimationData ResourceManager::ammoGiftData()
{
    auto ammo = AnimationData{};

    ammo.m_data[AnimationStatus_t::Round].emplace_back(30,   0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(30,   0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(30,   0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(533,  0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(533,  0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(533,  0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(1030, 0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(1030, 0, 390, 512);
    ammo.m_data[AnimationStatus_t::Round].emplace_back(1030, 0, 390, 512);

    return ammo;
}