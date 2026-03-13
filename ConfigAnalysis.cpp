#include "ConfigAnalysis.hpp"
#include <sstream>

namespace ms {
InputAnalysis::Input ConfigAnalysis:check (const std::string& inp) const {
  if (inp == "easy" || inp == "Easy" || inp == "normal" || inp == "Normal" || inp == "hard" || inp == "Hard") {
    return DifficultyIn {inp};
  }
  int sz;
  std::stringstream st(inp);
  if (st >> sz) {
    return SizeIn {sz, sz};
  }
  return InvalidIn {};
}
}
