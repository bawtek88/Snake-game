# Snake-game
A simple 2D Snake game writen in C++ using SFML.

## Features
- Player-controlled snake
- Score tracking
- Configurable board size
- Enemy snake with basic(for now) AI

## Requirements
- C++ compiler with C++17 support
- [CMake](https://cmake.org/)
- [SFML](https://www.sfml-dev.org/)

## How to build
```bash
cmake -B build
cmake --build build
```

After building, run the executable from the ```build``` directory

## Configuration
Settings are configurable in ```assets/config.txt```:

```boardWidth```, ```boardHeight``` - size of the grid in **cells**  
```tickSpeed``` - time in seconds between each frame(recommended value is ```0.1``` for smooth image)  
```cellSize``` - size of a cell in pixels  

Changing the settings **doesn't** require rebuilding the project.

## Planned features
Next features are: More difficulty settings, save system, shop based on total score with more skins and backgrounds available.
