#include <memory>
#include <vector>
#include "SDL.h"
#include <iostream>

class Node {
    public:
        //getters
       int GetX() {return x_;}
       int GetY() {return y_;}
       //setters
       void SetX(int x) {if(x >=0) x_ = x;} // coordinates cannot be greater than 0
       void SetY(int y) {if(y >=0) y_ = y;} // coordinates cannot be greater than 0

       int distance;
       bool visited;
       

    private:
    int x_{0};
    int y_{0};
};


class SmartBot {
    public:
        ~SmartBot() {std::cout << "Djikstra algorithm finished for the current state" << std::endl; nodelist.clear(); path_points.clear();};

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