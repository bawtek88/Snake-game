#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Game.hpp"
#include "Config.hpp"

int main() 
{
    Config config = loadConfig("assets/config.txt");
    int width = config.boardWidth; //size of the board in cells
    int height = config.boardHeight;
    const float tickSpeed = config.tickSpeed; //time in seconds between each game update
    const float cellSize = config.cellSize; //size of cells in pixels
    bool start = false;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Game game(width, height);
    
    unsigned int uWidth = static_cast<unsigned int>(width) * cellSize;
    unsigned int uHeight = static_cast<unsigned int>(height) * cellSize;
    sf::RenderWindow window(sf::VideoMode({uWidth, uHeight}), "snake");

    //food
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(cellSize, cellSize));
    rectangle.setFillColor(sf::Color::Red);

    //snake
    sf::RectangleShape snakeBodyPart;
    snakeBodyPart.setSize(sf::Vector2f(cellSize, cellSize)); 
    snakeBodyPart.setFillColor(sf::Color::Green);

    sf::RectangleShape enemyBodyPart;
    enemyBodyPart.setSize(sf::Vector2f(cellSize, cellSize));
    enemyBodyPart.setFillColor(sf::Color::Blue);

    sf::Clock clock;

    sf::Font font;
    if(!font.openFromFile("assets/Pixel Digivolve.otf"))
    {
        std::cout << "Font failed to load\n";
    }

    sf::Text text(font);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({10.f, 10.f});
    
    sf::Text startText(font);
    sf::Time elapsed = clock.getElapsedTime();
    startText.setFont(font);
    startText.setCharacterSize(48);
    startText.setFillColor(sf::Color::White);
    
    startText.setString(std::to_string(int(elapsed.asSeconds())));
    startText.setPosition({uWidth/2.f, uHeight/2.f});

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up || keyPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    game.setSnakeDirection(Direction::UP);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down || keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    game.setSnakeDirection(Direction::DOWN);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left || keyPressed->scancode == sf::Keyboard::Scancode::A)
                {
                    game.setSnakeDirection(Direction::LEFT);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right || keyPressed->scancode == sf::Keyboard::Scancode::D)
                {
                    game.setSnakeDirection(Direction::RIGHT);
                }
            }
        }
        window.clear();
        text.setString("Score: " + std::to_string(game.getScore()));
        elapsed = clock.getElapsedTime();
        if(!start)
        {
            startText.setString(std::to_string(int(3.f-elapsed.asSeconds())));
            window.draw(startText);
            if(elapsed.asSeconds() > 3.f)
            {
                start = true;
                clock.restart();
            }
        }
        if(elapsed.asSeconds() > tickSpeed && start)
        {
            game.update();
            Cell next = game.getSnake().getNextHead();
            Cell nextEnemy = game.getEnemy().getNextHead();//verify behavior
            clock.restart();
        }
        
        bool isHead = true;
        bool isEnemyHead = true;
        if(start)
        {
            for(const Cell& bodyPart : game.getSnake().getBody())
            {

                snakeBodyPart.setPosition({bodyPart.x*cellSize, bodyPart.y*cellSize});
                if(isHead)
                {
                    snakeBodyPart.setFillColor(sf::Color::Yellow);
                    isHead = false;
                }
                else
                {
                    snakeBodyPart.setFillColor(sf::Color::Green);
                }
                window.draw(snakeBodyPart);
            
            }
            if(game.isEnemyAlive())
            {
                for(const Cell& bodyPartEnemy : game.getEnemy().getBody())
                {

                    enemyBodyPart.setPosition({bodyPartEnemy.x*cellSize, bodyPartEnemy.y*cellSize});
                    if(isEnemyHead)
                    {
                        enemyBodyPart.setFillColor(sf::Color::Yellow);
                        isEnemyHead = false;
                    }
                    else
                    {
                        enemyBodyPart.setFillColor(sf::Color::Blue);
                    }
                    window.draw(enemyBodyPart);
                
                }
            }
        }
        rectangle.setPosition({game.getFood().x*cellSize, game.getFood().y*cellSize});
        if(start)
        {
            window.draw(rectangle);
            window.draw(text);
        }
       
        window.display();
    }
    std::cout << "Final score is: "<< game.getScore() << std::endl;
}