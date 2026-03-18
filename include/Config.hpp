#pragma once
#include <string>

struct Config
{
    int boardWidth;
    int boardHeight;
    float tickSpeed;
    float cellSize;
};

Config loadConfig(const std::string& path);