#include "game.h"
#include "SDL.h"
#include <memory>
#include <vector>
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class SmartBot {
public:
    SmartBot(double rank, std::size_t grid_width, std::size_t grid_height);
    ~SmartBot() {};

    void Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration, Snake &snake);
    void RunGeneticAlgorithm(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration, Snake &snake);

    void SetRank(double rank) {rank_ = rank;}
    double GetRank() {return rank_;}

    std::vector<std::unique_ptr<SmartBot>> Solutions;
    Game game;

private: 
    double rank_{0.};

    void RunFitnessFunctionOnSolutions();
    void SortSolutionsByRank();
    double ComputeFitnessCoefficient();
    double ComputeRank();
};