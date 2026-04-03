#pragma once

#include "Direction.hpp"
#include "Snake.hpp"
#include "Player.hpp"
class Game
{
private:
    int boardWidth;
    int boardHeight;
    Snake snake;
    Snake enemy;
    Player player;
    Cell food;
    int score;
    bool playerAlive;
    bool enemyAlive;
    bool gameOver;
    void spawnFood();
    bool isOutOfBounds(const Cell& cell) const;

public:
    Game(int width, int height);
    void update();
    void setSnakeDirection(Direction newDirection);
    void setEnemyDirection(Difficulty difficulty, const Cell& enemyHead, const Cell& food);
    const Snake& getSnake() const;
    const Snake& getEnemy() const;
    Cell getFood() const;
    int getScore() const;
    Player getPlayer() const;
    bool isGameOver() const;
    bool isEnemyAlive() const;

};