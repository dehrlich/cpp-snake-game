#ifndef TREASURE_H
#define TREASURE_H

#include "SDL.h"
#include <random>
#include <chrono>


class Treasure { // : public Game {
    public:
    Treasure(int x, int y, int score);
    ~Treasure();

    // getter and setter methods
    void SetValue(int score);
    int GetValue();
    void SetLife();
    std::chrono::time_point<std::chrono::system_clock> GetLife();
    bool CheckTreasure(); // check if treasure is still valid
    void SetTreasure(bool x); // set treasure _exists to "true"
    SDL_Point GetCoord();
    void SetCoord(int x, int y);

    private:
    // need to set up getters/setters to access and modify all these private member variables
    bool _exists;
    int _treasure_value;
    std::chrono::time_point<std::chrono::system_clock> _treasure_life; // how long treasure will be present
    SDL_Point _treasure; // has an x and y private member

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_treasure_value;
    std::uniform_int_distribution<int> random_treasure_life;

};

#endif