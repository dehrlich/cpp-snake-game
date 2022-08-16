#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "treasure.h"

//class Treasure;

class Game {
 public:
  Game();
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game(); // to delete treasure which was created on the heap
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void SpawnTreasure();
  void DeleteTreasure();

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

 private:
  Snake snake;
  SDL_Point food;
  Treasure *treasure;
  /*
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  */
  int score{0};

  void PlaceFood();
  //void PlaceTreasure();
  void Update();
};

#endif