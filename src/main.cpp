#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "smartbot.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Snake snake(kGridWidth, kGridHeight);
  SmartBot bot(0., kGridWidth, kGridHeight);
  bot.RunGeneticAlgorithm(controller, renderer, kMsPerFrame);
  return 0;
}