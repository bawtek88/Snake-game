#pragma once

#include "Cell.hpp"
#include "Direction.hpp"
#include <deque>

class Snake
{
private:
    std::deque<Cell> body;
    Direction direction;

public:

    Snake();
    Snake(const std::deque<Cell>& initialBody, Direction initialDirection);

    void move(bool grow);
    void setDirection(Direction newDirection);
    const std::deque<Cell>& getBody() const;
    bool occupiesCell(const Cell& cell) const;
    
    Direction getDirection() const;
    Cell getHead() const;
    Cell getNextHead() const;
    
    bool hitsItself(const Cell& nextHead, bool willGrow, const std::deque<Cell>& body) const; //used for self collision and collision with other snake

};