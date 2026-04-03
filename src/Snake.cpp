#include "Snake.hpp"
Snake::Snake()
{
    std::deque<Cell> initialBody = {{10, 10}, {9, 10}, {8, 10}};
    body = initialBody;
    direction = Direction::RIGHT;
}

Snake::Snake(const std::deque<Cell>& initialBody, Direction initialDirection)
{
    body = initialBody;
    direction = initialDirection;
}

const std::deque<Cell>& Snake::getBody() const
{
    return body;
}

Direction Snake::getDirection() const
{
    return direction;
}
void Snake::setDirection(Direction newDirection)
{
    Direction currDirection = getDirection();
    if(currDirection == Direction::UP && newDirection == Direction::DOWN) return;
    if(currDirection == Direction::DOWN && newDirection == Direction::UP) return;
    if(currDirection == Direction::LEFT && newDirection == Direction::RIGHT) return;
    if(currDirection == Direction::RIGHT && newDirection == Direction::LEFT) return;
    direction = newDirection;
}

bool Snake::occupiesCell(const Cell& cell) const
{
    for(const Cell& bodyPart : body)
    {
        if(cell.x == bodyPart.x && cell.y == bodyPart.y)
        return true;
    }
    return false;
}

bool Snake::hitsItself(const Cell& nextHead, bool willGrow, const std::deque<Cell>& body) const
{
    if(willGrow==true)
    {
        for(const Cell& bodyPart : body)
        {
            if(nextHead.x == bodyPart.x && nextHead.y == bodyPart.y)
            {
                return true;
            }
            
        }
        return false;
    }
    else
    {
        for(size_t i = 0; i < body.size()-1; i++)
        {
            if(nextHead.x == body[i].x && nextHead.y == body[i].y)  //we start the iteration from the beginning, so we don't have to exclude the tail
            {
                return true; 
            }
        }
        return false;
    }
}



void Snake::move(bool grow)
{
Cell nextHead = getNextHead();
body.push_front(nextHead);
    if(!grow)
    {
        body.pop_back();
    }
}

Cell Snake::getHead() const
{
    return body.front();
}

Cell Snake::getNextHead() const
{
    Cell head = getHead();
    Direction direction = getDirection();
    if(direction == Direction::UP)
    {
        head.y -= 1;
    }
    else if(direction == Direction::DOWN)
    {
        head.y += 1;
    }
    else if(direction == Direction::LEFT)
    {
        head.x -= 1;
    }
    else if(direction == Direction::RIGHT)
    {
        head.x += 1;
    }
    return head;
}