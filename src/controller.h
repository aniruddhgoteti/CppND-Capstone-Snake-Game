#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake);
  void ChooseDirection(int random_number);

  int GetUp() {return up_;}
  int GetDown() {return down_;}
  int GetLeft() {return left_;}
  int GetRight() {return right_;}
  void SetUp(int up) {up_ = up;}
  void SetDown(int down) {down_ = down;}
  void SetLeft(int left) {left_ = left;}
  void SetRight(int right) {right_ = right;}

private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  int up_{0};
  int down_{0};
  int left_{0};
  int right_{0};
};

#endif