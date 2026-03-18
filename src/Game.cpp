#include "Game.hpp"
#include <cstdlib>
Game::Game(int width, int height) : boardWidth(width), boardHeight(height), score(0), gameOver(false)
{
    spawnFood();
}

void Game::update()
{
    if(gameOver)
    {
        return;
    }

    Cell nextHead = snake.getNextHead();
    if(isOutOfBounds(nextHead))
    {
        gameOver = true;
        return;
    }

    bool willGrow = false;
    if(nextHead.x==food.x && nextHead.y==food.y)
    {
        willGrow = true;
    }

    if(snake.hitsItself(nextHead, willGrow))
    {
        gameOver = true;
        return;
    }
    
    snake.move(willGrow);
    if(willGrow)
    {
        score++;
        spawnFood(); 
    }
}

void Game::setSnakeDirection(Direction newDirection)
{
    snake.setDirection(newDirection);
}

const Snake& Game::getSnake() const
{
    return snake;
}

Cell Game::getFood() const
{
    return food;
}

int Game::getScore() const
{
    return score;
}

bool Game::isGameOver() const
{
    return gameOver;
}

void Game::spawnFood()
{
    food.x = rand() % boardWidth;
    food.y = rand() % boardHeight;

    while(snake.occupiesCell(food))
    {
        food.x = rand() % boardWidth;
        food.y = rand() % boardHeight;
    }
}

bool Game::isOutOfBounds(const Cell& cell) const
{
    if(cell.x < 0 || cell.x >= boardWidth || cell.y < 0 || cell.y >= boardHeight)
    {
        return true;
    }
    else
    {
        return false;
    }
}