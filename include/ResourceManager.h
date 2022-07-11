#pragma once

#include "Macros.h"
#include "Animation.h"

//class the responsible for all the resources in the game
class ResourceManager
{
public:
    
    static ResourceManager& instance();

    const sf::Sprite getSprite(enum Textures_t image) { return sf::Sprite(m_textures[int(image)]); }

    const sf::Texture & getTexture(enum Textures_t image) { return m_textures[int(image)]; }
   
    sf::SoundBuffer* getSound(const int);

    void loadSoundFromBuffer();

    std::vector<sf::Sound> getSoundVec();

    bool getMute();

    void setMute(bool stat);

    void playBackRoundSound(const bool);

    void loadTexture(Textures_t, const std::string&);

    void loadSound(sounds pos, const std::string& name);

    void loadFont(const std::string& name);

    const sf::Font& getFont() const;

    AnimationData playerData();

    AnimationData robotEnemyData();

    AnimationData dinoEnemyData();

    AnimationData coinData();

    AnimationData hpGiftData();

    AnimationData lifeGiftData();

    AnimationData ammoGiftData();

    const AnimationData& animationData(ObjectsData_t objectsData) { return m_animationsData[objectsData]; }

private:
    ~ResourceManager();

    ResourceManager();
    ResourceManager(const ResourceManager&) = default;
    void createSound();

    std::vector<sf::Texture> m_textures;
    std::vector<AnimationData> m_animationsData;
    std::vector<sf::SoundBuffer> m_soundVec;
    std::vector<sf::Sound> m_sound;
    sf::Sound m_BackRoundsound;

    bool m_mute = false;

    sf::Font m_font;
};






