#include "game.h"
#include <iostream>
#include "SDL.h"
//#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      treasure(nullptr),
      lastUpdate(std::chrono::system_clock::now()) {
  PlaceFood();
  //PlaceTreasure();
}

Game::Game() {}

Game::~Game() {
  if(treasure != nullptr) // delete any dynamic memory to avoid memory leaks
    {
        delete treasure;
        treasure = nullptr;
    }
}

void Game::DeleteTreasure() {
  if(treasure != nullptr) // delete any dynamically allocated memory during gameplay
    {
        delete treasure;
        treasure = nullptr;
    }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  //std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  // init stop watch
  //lastUpdate = std::chrono::system_clock::now();

  while (running) {
    frame_start = SDL_GetTicks();

    //every 3 seconds, place some treasure
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    
    if (timeSinceLastUpdate >= 3000 && treasure == nullptr) { // spawn treasure and notify game
      SpawnTreasure();
    }
    /*
    else if (timeSinceLastUpdate >= 3000 && treasure->CheckTreasure() == false) {
      treasure->SetTreasure(true);
      treasure->SetLife();
      treasure->SetValue(GetScore());
    }
    */

    if (treasure != nullptr && treasure->CheckTreasure() == true) {
      //check if treasure's life has timed out
      long treasure_life = std::chrono::duration_cast<std::chrono::milliseconds>(treasure->GetLife() - std::chrono::system_clock::now()).count();
      if (treasure_life <= 0) {
        // treasure->SetTreasure(false);
        DeleteTreasure();
        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, snake);
        Update();
        renderer.Render(snake, food);
        lastUpdate = std::chrono::system_clock::now();
      }
      else { // treasure is still alive and can be validly captured
        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, snake);
        Update();
        if (treasure != nullptr) { // make sure the treasure object wasn't deleted on the heap due to being captured
          renderer.Render(snake, food, treasure->GetCoord()); //use overloaded Render func
        }
        else {
          renderer.Render(snake, food);
        }
      }
    }
    else { // no current treasure object on the heap
      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake);
      Update();
      renderer.Render(snake, food);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::SpawnTreasure() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item or food before placing
    // treasure. If clear, spin up Treasure object on the heap
    if (!snake.SnakeCell(x, y) && (x != food.x && y !=food.y)) {
      treasure = new Treasure(x, y, GetScore());
      return; // note: in Udpate function, must check life of treasure, see if
      // if it needs to be removed
    }
  }
}

/*
void Game::PlaceTreasure() {
  int x, y;
  while (treasure->CheckTreasure()) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item or food before placing
    // treasure. If clear, spin up Treasure object on the heap
    if (!snake.SnakeCell(x, y) && (x != food.x && y !=food.y)) {
      treasure = new Treasure(x, y);
      return; // note: in Udpate function, must check life of treasure, see if
      // if it needs to be removed
    }
  }
}
*/

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if treasure exists, and if so, did snake catch the treasure
  if (treasure != nullptr && treasure->CheckTreasure() == true) { // might not be necessary since already checked in Game::Run
      if (treasure->GetCoord().x == new_x && treasure->GetCoord().y == new_y) {
        score += treasure->GetValue();
        //treasure->SetTreasure(false); // signal to remove treasure from game board
        DeleteTreasure();
        snake.CutBody(); // cut snake body in half as reward
        lastUpdate = std::chrono::system_clock::now();
      }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }