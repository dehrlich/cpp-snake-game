#include "treasure.h"
#include <random>
#include <chrono>


Treasure::Treasure(int x, int y, int score) : _exists(true) {
    _treasure.x = x;
    _treasure.y = y;

    std::uniform_int_distribution<int> random_treasure_value(1, (score + 1)); // treasure may be worth from 1 up to current score
    
    _treasure_value = random_treasure_value(engine);

    // treasure may appear on grid for 1-4 secs
    // using milliseconds for more granular timing
    std::uniform_int_distribution<int> random_treasure_life(1000, 4000);

    _treasure_life = std::chrono::system_clock::now() + std::chrono::milliseconds(random_treasure_life(engine));
}

Treasure::~Treasure() {}

// define all getters / setters

bool Treasure::CheckTreasure() { return _exists; }

void Treasure::SetTreasure(bool x) { _exists = x; }

std::chrono::time_point<std::chrono::system_clock> Treasure::GetLife() { return _treasure_life; }

void Treasure::SetLife(){

    // treasure may appear on grid for 1-4 secs
    // using milliseconds for more granular timing
    std::uniform_int_distribution<int> distr(1000, 4000);
    _treasure_life = std::chrono::system_clock::now() + std::chrono::milliseconds(distr(engine));

}

int Treasure::GetValue() { return _treasure_value; }

void Treasure::SetValue(int score) {

    std::uniform_int_distribution<int> distr(1, score); // treasure may be worth 1 up to current score
    _treasure_value = distr(engine);

}

SDL_Point Treasure::GetCoord() { return _treasure; }

void Treasure::SetCoord(int x, int y) {
    _treasure.x = x;
    _treasure.y = y;
}