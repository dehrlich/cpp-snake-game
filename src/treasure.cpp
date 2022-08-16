#include "treasure.h"
//#include "game.h"
#include <random>
#include <chrono>


Treasure::Treasure(int x, int y) : _exists(true) {
    // needs to happens in Game object to make sure it doesn't overlap with snake
    //x = random_w(engine); ?? 
    //y = random_h(engine); ??
    _treasure.x = x;
    _treasure.y = y;

    std::uniform_int_distribution<int> distr(1, GetScore()); // treasure may be worth 1 up to current score
    
    _treasure_value = distr(engine);

    // treasure may appear on grid for 1-4 secs
    // using milliseconds for more granular timing
    std::uniform_int_distribution<int> distr(1000, 4000);

    _treasure_life = std::chrono::system_clock::now() + std::chrono::milliseconds(distr(engine));
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

void Treasure::SetValue() {

    std::uniform_int_distribution<int> distr(1, GetScore()); // treasure may be worth 1 up to current score
    _treasure_value = distr(engine);

}

SDL_Point Treasure::GetCoord() { return _treasure; }

void Treasure::SetCoord(int x, int y) {
    _treasure.x = x;
    _treasure.y = y;
}