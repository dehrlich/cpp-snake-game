#ifndef TREASURE_H
#define TREASURE_H

#include "SDL.h"

class Treasure {
    public:
    Treasure();
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
    void set_value();
    void set_life();

    private:
    int _treasure_value;
    long _treasure_life; // how long treasure will be present in milliseconds
    SDL_POINT _treasure;

};

#endif