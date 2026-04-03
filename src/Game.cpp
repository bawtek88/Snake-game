#include "Game.hpp"
#include <cstdlib>
#include <iostream>
#include "Player.cpp"
Game::Game(int width, int height) : boardWidth(width), boardHeight(height), score(0), gameOver(false), playerAlive(true), enemyAlive(true)
{
    player = Player();

    std::deque<Cell> playerBody = {{5, height/2}, {4, height/2}, {3, height/2}};
    snake = Snake(playerBody, Direction::RIGHT);
    
    std::deque<Cell> enemyBody = {{(width-5)/2, height/2}, {(width-5)/2+1, height/2}, {(width-5)/2+2, height/2}};
    enemy = Snake(enemyBody, Direction::DOWN);
    //Difficulty difficulty = player.getSelectedDifficulty();
    spawnFood();
}

void Game::update()
{
    if(!playerAlive)
    {
        gameOver = true;
        return;
    }
    if(gameOver)
    {
        return;
    }

    Cell nextHead = snake.getNextHead();
    if(isOutOfBounds(nextHead))
    {
        std::cout << "Player hit a wall\n";
        playerAlive = false;
    }
    
    Cell nextEnemyHead = enemy.getNextHead();
    if(isOutOfBounds(nextEnemyHead) && enemyAlive)
    {
        std::cout << "Enemy hit a wall\n";
        enemyAlive = false;
    }

    bool willGrow = false;
    if(nextHead.x==food.x && nextHead.y==food.y)
    {
        willGrow = true;
    }

    bool willEnemyGrow = false;
    if(nextEnemyHead.x==food.x && nextEnemyHead.y==food.y && enemyAlive)
    {
        willEnemyGrow = true;
    }
    
    if(snake.hitsItself(nextHead, willGrow, snake.getBody())) //collision with itself
    {
        std::cout << "Player hit itself\n";
        playerAlive = false;
        return;
    }

    if(enemy.hitsItself(nextEnemyHead, willEnemyGrow, enemy.getBody()) && enemyAlive) // enemy collision with itself
    {
        std::cout << "Enemy hit itself\n";
        enemyAlive = false;
    }

    if(snake.hitsItself(nextHead, willEnemyGrow, enemy.getBody()) && enemyAlive) // collision with enemy
    {
        std::cout << "Player hit enemy\n";
        playerAlive = false;
        return;
    }
    if(enemy.hitsItself(nextEnemyHead, willEnemyGrow, snake.getBody()) && enemyAlive) // enemy collision with  player
    {
        std::cout << "Enemy hit player\n";
        enemyAlive = false;
        return;
    }

    if(enemyAlive)
    {
        enemy.move(willEnemyGrow);
    }
    snake.move(willGrow);
    if(willGrow)
    {
        score++;
        spawnFood(); 
    }
    if(willEnemyGrow && enemyAlive)
    {
        spawnFood();
    }
    setEnemyDirection(getPlayer().getSelectedDifficulty(), enemy.getHead(), getFood());
}

void Game::setSnakeDirection(Direction newDirection)
{
    snake.setDirection(newDirection);
}

void Game::setEnemyDirection(Difficulty difficulty, const Cell& enemyHead, const Cell& food)
{
    //int visionRange = 5; //enemy can see the player and food within this range
    std::vector<Cell> possibleMoves = {{enemyHead.x, enemyHead.y-1}, {enemyHead.x, enemyHead.y+1}, {enemyHead.x-1, enemyHead.y}, {enemyHead.x+1, enemyHead.y}};
    std::vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    for(size_t i = 0; i < possibleMoves.size(); i++)
    {
        if(isOutOfBounds(possibleMoves[i]) || snake.occupiesCell(possibleMoves[i]) || enemy.occupiesCell(possibleMoves[i]))
        {
            possibleMoves.erase(possibleMoves.begin() + i);
            directions.erase(directions.begin() + i);
            i--;
        }
    }
    static int count = 0;
    count++;
    switch(difficulty)
    {
        case Difficulty::TRIVIAL:
            //if()
            if(true)
            {
                if(directions.size() > 0)
                {
                    if((abs(enemyHead.x-food.x) + abs(enemyHead.y-food.y)) < 100) //check range to food
                    {
                        if(enemyHead.x < food.x)
                        {
                            enemy.setDirection(Direction::RIGHT);
                        }
                        else if(enemyHead.x > food.x)
                        {
                            enemy.setDirection(Direction::LEFT);
                        }
                        else if(enemyHead.y < food.y)
                        {
                            enemy.setDirection(Direction::DOWN);
                        }
                        else if(enemyHead.y > food.y)
                        {
                            enemy.setDirection(Direction::UP);
                        }
                    }
                    else
                    {
                        enemy.setDirection(directions[rand() % directions.size()]);
                    }
                    
                }
            }
            break;
    }
}
bool Game::isEnemyAlive() const
{
    return enemyAlive;
}
const Snake& Game::getSnake() const
{
    return snake;
}

const Snake& Game::getEnemy() const
{
    return enemy;
}

Cell Game::getFood() const
{
    return food;
}

int Game::getScore() const
{
    return score;
}
Player Game::getPlayer() const
{
    return player;
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
