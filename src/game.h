#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "smartbot.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  Snake snake;
  SDL_Point food;
  SmartBot smartbot;

  void PlaceFood();
  void Update();

 private:

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::unique_ptr<SmartBot> bot;
  SDL_Point start_point{};
  SDL_Point end_point{};

  int score{0}; // score (i.e no of times the food is eaten) of a game
};

#endif