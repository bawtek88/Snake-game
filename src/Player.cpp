#include "Player.hpp"

Player::Player()
{
    name = "";
    selectedDifficulty = Difficulty::TRIVIAL;
    totalScore = 0;
    highScore = 0;
    for(int i = 0; i < 10; i++) //termporarily set to 10, can be changed later
    {
        unlockedSkins.push_back(false);
        unlockedBackgrounds.push_back(false);
    }
    selectedSkin = 0;
    selectedBackground = 0;
}

void Player::setName(std::string name)
{
    this->name = name;
}
void Player::setTotalScore(int score)
{
    totalScore = score;
}
void Player::setUnlockedSkins(int skin)
{
    unlockedSkins[skin] = true;
}
void Player::setUnlockedBackgrounds(int background)
{
    unlockedBackgrounds[background] = true;
}
void Player::setSelectedSkin(int skin)
{
    selectedSkin = skin;
}
void Player::setSelectedBackground(int background)
{
    selectedBackground = background;
}
void Player::setHighScore(int score)
{
    highScore = score;
}
void Player::setSelectedDifficulty(Difficulty difficulty)
{
    selectedDifficulty = difficulty;
}

std::string Player::getName() const
{
    return name;
}
int Player::getTotalScore() const
{
    return totalScore;
}
const std::vector<bool>& Player::getUnlockedSkins() const
{
    return unlockedSkins;
}
const std::vector<bool>& Player::getUnlockedBackgrounds() const
{
    return unlockedBackgrounds;
}
int Player::getSelectedSkin() const
{
    for(size_t i = 0; i < unlockedSkins.size(); i++)
    {
        if(i == selectedSkin)
        {
            if(unlockedSkins[i])
            {
                return selectedSkin;
            }
            else
            {
                return 0;
            }
        }
    }
    return selectedSkin;
}
int Player::getSelectedBackground() const
{
    for(size_t i = 0; i < unlockedBackgrounds.size(); i++)
    {
        if(i == selectedBackground)
        {
            if(unlockedBackgrounds[i])
            {
                return selectedBackground;
            }
            else
            {
                return 0;
            }
        }
    }
    return selectedBackground;
}
int Player::getHighScore() const
{
    return highScore;
}
Difficulty Player::getSelectedDifficulty() const
{
    return selectedDifficulty;
}


