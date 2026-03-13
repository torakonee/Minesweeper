#include "Status.hpp"

namespace ms {
Status::Status(std::shared_ptr<Config> cfg) : cg(cfg) {}
void Status::plusMove() {
  moves++;
}
void Status::newFlag() {
  flagsam++;
}
void Status::gameOver() {
  st = State::GameOver;
}
void Status::victory() {
  st = State::Victory;
}
Status::State Status::getState() const {
  return state;
}
void Status::print() const {
  std::cout << "Moves: " << moves << std::endl << "Flags Placed: " << flagsam << std::endl << "Mines on the field: " << cg->getMines() << std::endl;
  if (state == state::GameOver) {
    std::cout << "Game Over ;-;" << std::endl;
  }
  if (state == state::Victory) {
    std::cout << "You Won! Congratulations!" << std::endl;
  }
}
