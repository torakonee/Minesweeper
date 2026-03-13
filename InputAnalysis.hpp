#pragma once
#include <string>
#include <variant>

namespace ms {
class InputAnalysis {
public:

  struct CoordinateIn {
    int x, y;
  };

  struct DifficultyIn {
    std::string difficulty;
  };

  struct SizeIn {
    int size;
  };

  struct DefualtIn {

  };

  struct InvalidIn {

  };

  using Input = std::variant<CoordinateIn, DifficultyIn, SizeIn, DefaultIn, InvalidIn>;

  virtual ~InputAnalysis() = default;

  virtual Input check(std::string inp) const = 0;
}
