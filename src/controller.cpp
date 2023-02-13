#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

constexpr std::size_t kGridWidth{32};
constexpr std::size_t kGridHeight{32};

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite or snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) {
  SDL_Event e;

  while (SDL_PollEvent(&e) or snake.alive) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else {
      if (GetUp() == 1) { 
         ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
                          std::cout << "Changed direction to Up!" << std::endl;
                          return;}
      else if (GetDown() == 1) {
         ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp); 
                          std::cout << "Changed direction to Down!" << std::endl;
                          return;}
      else if (GetLeft() == 1) {
         ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight); 
                          std::cout << "Changed direction to Left!" << std::endl;
                          return;}
      else {
         ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft); 
                          std::cout << "Changed direction to Right!" << std::endl;
                          return;}
    }
  }
}

void Controller::ChooseDirection(int random_number) {
    if (random_number == 1)
        {SetUp(1); SetDown(0); SetLeft(0); SetRight(0); return;}
    else if (random_number == 2)
        {SetDown(1); SetUp(0); SetLeft(0); SetRight(0); return;}
    else if (random_number == 3)
        {SetLeft(1); SetUp(0); SetDown(0); SetRight(0); return;}
    else
        {SetRight(1); SetDown(0); SetLeft(0); SetUp(0); return;}
}