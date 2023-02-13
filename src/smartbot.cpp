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
#include <assert.h>


SmartBot::SmartBot(double rank, std::size_t grid_width, std::size_t grid_height) 
         : game(grid_width, grid_height), rank_(rank) {}



double SmartBot::ComputeRank() {
  auto fitness = game.ComputeFitnessCoefficient();
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


bool comparemap(std::pair<double, Snake>& a,
        std::pair<double, Snake>& b)
{
    return a.first > b.first;
}


void SmartBot::SortRanksMap(std::map<double, Snake> &PassedMap) {
   std::vector<std::pair <double, Snake> > pairRanksVec;
   std::map<double, Snake> sortedRanksMap;
   
   for ( auto& it : PassedMap) {
      pairRanksVec.emplace_back( it );
   }
   PassedMap.clear();
   std::sort(pairRanksVec.begin(), pairRanksVec.end(), comparemap);
   
   for ( auto& it : pairRanksVec ) {
      PassedMap.insert({ it.first, it.second });
   }
   pairRanksVec.clear();
}


std::map<double, Snake> SmartBot::CreateRanksMap() {
  // create map
  std::transform(Ranks.begin(),Ranks.end(), game.SnakeCoordinates.begin(), std::inserter(RanksMap, RanksMap.end()), [](double ranks, Snake snake)
   {
      return std::make_pair(ranks, snake);
  });
}

void SmartBot::RunGeneticAlgorithm(Controller  &controller, Renderer &renderer,
               std::size_t target_frame_duration) {

  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  game.Run(controller, renderer, target_frame_duration);
  std::cout << "Game has terminated successfully!" << std::endl;
  std::cout << "Score: " << game.GetScore() << std::endl;
  std::cout << "Size: " << game.GetSize() << std::endl;

  for (auto &snake : game.SnakeCoordinates)
  {
    Solutions.emplace_back(new SmartBot(GetRank(), kGridWidth, kGridHeight));
  }

  RunFitnessFunctionOnSolutions();

  for (auto &sol : Solutions)
  {
    Ranks.emplace_back(sol->GetRank());
  }

  SortSolutionsByRank();

  assert(Ranks.size() == game.SnakeCoordinates.size());
  RanksMap = CreateRanksMap();
  //Ranks.clear();
  //game.SnakeCoordinates.clear();

  //SortRanksMap(RanksMap);

  for (auto &it: Ranks) {
    std::cout <<it << std::endl;
  }
}