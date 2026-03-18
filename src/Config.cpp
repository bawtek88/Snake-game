#include "Config.hpp"
#include <fstream>
#include <iostream>
#include <string>

Config loadConfig(const std::string& path)
{
    Config cfg;
    cfg.boardWidth = 100;
    cfg.boardHeight = 100;
    cfg.tickSpeed = 0.1f;
    cfg.cellSize = 10.f;
    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line))
    {
        size_t delimiterPos = line.find('=');
        if(delimiterPos != std::string::npos)
        {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            if(key == "boardWidth")
            {
                cfg.boardWidth = std::stoi(value);
            }
            else if(key == "boardHeight")
            {
                cfg.boardHeight = std::stoi(value);
            }
            else if(key == "tickSpeed")
            {
                cfg.tickSpeed = std::stof(value);
            }
            else if(key == "cellSize")
            {
                cfg.cellSize = std::stof(value);
            }
        }

     }
     return cfg;
}