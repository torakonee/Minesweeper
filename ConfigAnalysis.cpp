#include "ConfigAnalysis.hpp"
#include <sstream>

namespace ms {
InputAnalysis::Input ConfigAnalysis::check (const std::string& inp) const {
  if (inp == "easy" || inp == "Easy" || inp == "normal" || inp == "Normal" || inp == "hard" || inp == "Hard") {
    return InputAnalysis::DifficultyIn {inp};
  }
  int sz;
  std::stringstream st(inp);
  if (st >> sz) {
    return InputAnalysis::SizeIn {sz, sz};
  }
  return InputAnalysis::InvalidIn {};
}
}
