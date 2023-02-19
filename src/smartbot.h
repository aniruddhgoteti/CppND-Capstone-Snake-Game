#include <memory>
#include <vector>
#include "SDL.h"
#include <iostream>

class Node {
    public:
       Node* parent = nullptr;
       int GetX() {return x_;}
       int GetY() {return y_;}
       void SetX(int x) {x_ = x;}
       void SetY(int y) {y_ = y;}
       int distance;
       bool visited;
       

    private:
    int x_{0};
    int y_{0};
};


class SmartBot {
    public:
        ~SmartBot() {};

        std::vector<SDL_Point> ApplyDjikstra(const SDL_Point &start_point, const SDL_Point &end_point);

    private:
        int GetDistanceFromFood(const int start_point_x, const int start_point_y, const int end_point_x, const int end_point_y);
        int GetMinimumDistance();
        int CalculateDistanceFromFood(const int start_point_x, const int start_point_y, const int end_point_x, const int end_point_y);
        void printSolution();

        std::vector<SDL_Point> path_points;
        int Graph[32][32];
        SDL_Point path;
        Node node;
        std::vector<Node> nodelist;
};