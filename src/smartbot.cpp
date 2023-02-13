#include "smartbot.h"
#include "snake.h"
#include "game.h"
#include "controller.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


SmartBot::SmartBot(double rank = 0., std::size_t grid_width = 32, std::size_t grid_height = 32) 
         : game(grid_width, grid_height), rank_(rank) {}


double SmartBot::ComputeFitnessCoefficient() {
  double fitness = (std::abs(game.snake.head_x - game.food.x) + std::abs(game.snake.head_x - game.food.y)) * 0.01;
  return fitness;
}

double SmartBot::ComputeRank() {
  auto fitness = ComputeFitnessCoefficient();
  double rank = (fitness == 0) ? 99999 : std::abs(1.0/fitness);
  SetRank(rank);
}

void SmartBot::RunFitnessFunctionOnSolutions() {
  for (auto &solution : SmartBot::Solutions) {
    solution->ComputeRank();
  }
}

void SmartBot::SortSolutionsByRank() {
  std::sort(SmartBot::Solutions.begin(), SmartBot::Solutions.end(), [](const auto &lhs, const auto &rhs) {
    return lhs->GetRank() > rhs->GetRank();
  });
}


void SmartBot::RunGeneticAlgorithm(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, Snake &snake) {
  int NUM = 2;
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  for (int i = 0; i < NUM; i++)
  {
    std::cout << "Game has terminated successfully!" << std::endl;
    std::cout << "Score: " << game.GetScore() << std::endl;
    std::cout << "Size: " << game.GetSize() << std::endl;
    Solutions.emplace_back(new SmartBot(GetRank(), kGridWidth, kGridHeight));
  }

  RunFitnessFunctionOnSolutions();
  SortSolutionsByRank();
}