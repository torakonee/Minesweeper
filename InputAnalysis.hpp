#pragma once
#include <string>
#include <variant>

namespace ms {
class InputAnalysis {
public:

  struct CoordinateIn {
    int x, y;
    bool isFlag = false;
  };

  enum class Difficulty {
    Easy,
    Normal,
    Hard
  };

  struct DifficultyIn {
    Difficulty difficulty;
  };

  struct SizeIn {
    int size1;
    int size2;
  };

  struct DefaultIn {

  };

  struct InvalidIn {

  };

  using Input = std::variant<CoordinateIn, DifficultyIn, SizeIn, DefaultIn, InvalidIn>;

  virtual ~InputAnalysis() = default;

  virtual Input check(const std::string& inp) const = 0;
};
}
