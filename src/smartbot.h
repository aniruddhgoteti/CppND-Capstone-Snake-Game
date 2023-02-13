#include "game.h"
#include "SDL.h"
#include <memory>
#include <vector>
#include <map>
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class SmartBot {
public:
    SmartBot(double rank, std::size_t grid_width, std::size_t grid_height);
    ~SmartBot() {};

    void Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration, Snake &snake);
    void RunGeneticAlgorithm(Controller &controller, Renderer &renderer,
        std::size_t target_frame_duration);

    void SetRank(double rank) {rank_ = rank;}
    double GetRank() {return rank_;}

    Game game;
    Controller control;

    std::vector<std::unique_ptr<SmartBot>> Solutions;
    std::vector<double> Ranks;
    std::map<double, Snake> RanksMap;

private: 
    double rank_{0.};

    void RunFitnessFunctionOnSolutions();
    void SortSolutionsByRank();
    double ComputeRank();
    void SortRanksMap(std::map<double, Snake> &PassedMap);
    std::map<double, Snake> CreateRanksMap();
};