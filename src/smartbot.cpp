#include <iostream>
#include <vector>
#include <algorithm>
#include "SDL.h"
#include <limits.h>
#include "smartbot.h"

# define BOARD_SIZE 32

// calculate absolute distance from snake head to food
int SmartBot::CalculateDistanceFromFood(const int start_point_x, const int start_point_y, const int end_point_x, const int end_point_y) {
    return abs(end_point_x - start_point_x) + abs(end_point_y - start_point_y);
}

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
int SmartBot::GetMinimumDistance() {
  int min = INT_MAX;
  int min_index;
  
  for(auto &node: nodelist) {
  if ((!node.visited) and node.distance < min) {
    min = node.distance;
    min_index = &node - &nodelist[0];
  }}

  return min_index;
}


std::vector<SDL_Point> SmartBot::ApplyDjikstra(const SDL_Point &start_point, const SDL_Point &end_point) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
          node.distance = INT_MAX;
          node.visited = false;
          node.SetX(i);
          node.SetY(j); 
          nodelist.emplace_back(node);

          Graph[i][j] = CalculateDistanceFromFood(i, j, end_point.x, end_point.y);
        }
    }

    
    for(auto &node : nodelist) {
      if(node.GetX() == end_point.x and node.GetY() == end_point.y) {
        node.distance = 0;
      }
    }

  
    for(int i = 0; i < nodelist.size() - 1; i++) {
        auto min_index = GetMinimumDistance();
        nodelist[min_index].visited = true;
        for(int visit = 0; visit < nodelist.size(); visit++) {
           if ((!nodelist[visit].visited) and Graph[nodelist[min_index].GetX()][visit] and (nodelist[min_index].distance != INT_MAX)
                and nodelist[min_index].distance + Graph[nodelist[min_index].GetX()][visit] < nodelist[visit].distance) {
                        nodelist[visit].distance = nodelist[visit].distance + Graph[nodelist[min_index].GetX()][visit];
                }
          }       
    }

  std::sort(nodelist.begin(), nodelist.end(), [](const Node &a, const Node &b){ return (a.distance) < (b.distance); });
  std::vector<Node> nodelist_best(nodelist.begin(), nodelist.begin() + 25);

  for (auto &node: nodelist_best) {
    path.x = node.GetX();
    path.y = node.GetY();
    path_points.emplace_back(path);
  }
  return path_points;
}

