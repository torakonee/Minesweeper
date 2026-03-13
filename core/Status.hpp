#pragma once
#include <iostream>
#include <memory>
#include "../Config/Config.hpp"

namespace ms {
class Status {
  public:
  enum class State {
    InProgress,
    GameOver,
    Victory
  };
  explicit Status(std::shared_ptr<Config> cg);
  void plusMove();
  void newFlag();
  void gameOver();
  void victory();
  State getState() const;
  void print() const;
private:
  
  int moves = 0;
  int flagsam = 0;
  std::shared_ptr<Config> cg;
  State st = State::InProgress;
};
}
