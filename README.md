# CPPND: Capstone Snake Game

## Project Motivation

- This is a project to improve c++ skills, including OOP design, and memory management. The base code is from [this](https://github.com/udacity/CppND-Capstone-Snake-Game) repo. This project is part of the larger [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

- This project makes several changes to the base code to implement a new aspect to the game, specifically the notion of capturing "treasure."
  - A new "Treasure" class is implemented to create new Treasure objects. The class logically organized, with class attributes to hold the data, and class methods to perform tasks. Class data is explicitly specified as public or private, and appropriate getter/setter functions are implemented to access private members if necessary (See Treasure.h and Treasure.cpp, all lines).
  - State is accessed via member functions (see Treasure.h, lines 16,18,19,21 and Treasure.cpp, lines 25, 29, 40, 49)
  - The treasure objects are created dynamically at run time on the heap (see game.cpp, lines 50 and 130). The treasure objects only have a short lifespan, picked from a random distribution (using the random library) with a lifespan between 1 and 4 seconds (see treasure.cpp, lines 16 and 18).
  - If the user does not capture the treasure before the life expires, the treasure object is deleted and memory is freed so as to be memory efficient (see game.cpp, line 57).
  - The project uses control structures to determine if a treasure object should be spawned, if is has been captured, if it's lifespan has expired, and accordingly if if needs to be deleted (see game.cpp lines 46-81).
  - A destructor `Game::~Game()` is implementd to make sure any treasure objects are cleaned up before game play is ended and to ensure memory leakes are prevented (see game.cpp, line 18)
  - In the renderer.cpp, the function `void Renderer::Render` is overloaded to take the additional argument of `SDL_Point const &treasure` in the case a treasure object exists and needs to be rendered on the game board (see renderer.cpp, line 78-120).
- If a user does successfuly capture the treasure object before it's lifespan has expired, they are rewarded with a point increase dictated by a random number picked from the uniform distribution between 1 and the current score. Moreover, the length of the snake is cut in half to give the user more manueverability on the game board.

## File Descriptions

    CppND-Capstone-Snake-Game
    |- build # cmake files, Makefile, executable
    |- cmake # cmake for SDL2 library
    |- src
    | |- controller.cpp # handle user input, change direction of snake
    | | - controller.h # header file for controller.cpp
    | | - game.cpp # instantiate instance of game, spawn snake, food, treasure. Update gameplay. Call rendering class.
    | | - game.h
    | | - main.cpp # instantiate game board, game instance, renderer instance, and controller instance. 
    | | - renderer.h
    | | - renderer.cpp # class to render game board, snake, food, treasure.
    | | - snake.cpp # class to handle snake attributes, methods. Govern snake behavior.
    | | - snake.h
    | | - treasure.cpp # class to handle treasure attributes, methods. Govern treasure behavior.
    | | - treasure.h
    .gitignore
    CMakeLists.txt
    CODEOWNERS
    LICENSE.md
    README.md

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
