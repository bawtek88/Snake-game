#pragma once

#include "Direction.hpp"
#include "Snake.hpp"

class Game
{
private:
    int boardWidth;
    int boardHeight;
    Snake snake;
    Cell food;
    int score;
    bool gameOver;
    void spawnFood();
    bool isOutOfBounds(const Cell& cell) const;

public:
    Game(int width, int height);
    void update();
    void setSnakeDirection(Direction newDirection);

    const Snake& getSnake() const;
    Cell getFood() const;
    int getScore() const;
    bool isGameOver() const;

};