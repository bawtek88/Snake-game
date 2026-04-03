#pragma once
#include <string>
#include <vector>
#include "Difficulty.hpp"

class Player
{
    private:
        std::string name;
        int totalScore;
        std::vector<bool> unlockedSkins;
        std::vector<bool> unlockedBackgrounds;
        int selectedSkin;
        int selectedBackground;
        int highScore;
        Difficulty selectedDifficulty;
    public:
        Player();
        std::string getName() const;
        int getTotalScore() const;
        const std::vector<bool>& getUnlockedSkins() const;
        const std::vector<bool>& getUnlockedBackgrounds() const;
        int getSelectedSkin() const;
        int getSelectedBackground() const;
        int getHighScore() const;
        Difficulty getSelectedDifficulty() const;

        void setName(std::string name);
        void setTotalScore(int score);
        void setUnlockedSkins(int skin);
        void setUnlockedBackgrounds(int background);
        void setSelectedSkin(int skin);
        void setSelectedBackground(int background);
        void setHighScore(int score);
        void setSelectedDifficulty(Difficulty difficulty);
};