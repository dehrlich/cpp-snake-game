#ifndef TREASURE_H
#define TREASURE_H

#include "SDL.h"
#include "game.h"
//#include <random>
//#include <chrono>

//class Game; // forward declaration

class Treasure { // : public Game {
    public:
    Treasure(int x, int y, int score);
    ~Treasure();
    //allocate on the heap
    //deallocate in the destructor
    //spawn treasure items in a thread
    //use future and promises
    //use mutex and lock guard to cut snake length by a random amount (not to exceed length of snake less its head)
    //increase score by random amnt (not to exceed existing score itself)
    //look at PlaceFood() in game.cpp to see how to place the treasure
    //color of treasure should be different from food (red?)
    //while the treasure is a separate class, it will be instantiated (at random) within the game.cpp run method
    //add CutBody method to snake class to be invoked if user successfully captures treasure
    //update renderer.cpp to render food only if it exists (add condition checks)

    //things to keep in mind: treasure needs to stay on grid until it's lifetime expires (3 sec) - Add that to current
    //time using chrono:now, set that as _treasure_life, on each update, see if the time is past and if so, remove the treasure
    //use random module to pick random number 0-100, if number between 80-89, instantiate a treasure
    //if snake eats treasure, must cut snake length and update score


    // getter and setter methods
    void SetValue(int score);
    int GetValue();
    void SetLife();
    std::chrono::time_point<std::chrono::system_clock> GetLife();
    bool CheckTreasure(); // check if treasure is still valid
    void SetTreasure(bool x); // set treasure _exists to "true"
    SDL_Point GetCoord();
    void SetCoord(int x, int y);

    //bool _exists;
    //SDL_POINT _treasure; // has an x and y private member
    //int _treasure_value;
    //long _treasure_life; // how long treasure will be present in milliseconds

    private:
    // need to set up getters/setters to access and modify all these private member variables
    bool _exists;
    int _treasure_value;
    std::chrono::time_point<std::chrono::system_clock> _treasure_life; // how long treasure will be present
    SDL_Point _treasure; // has an x and y private member

    // inherited from class Game
    std::random_device dev;
    std::mt19937 engine;
    /*
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    */

    //void PlaceTreasure(); // define here or in game.cpp?
    //void Update();

};

#endif