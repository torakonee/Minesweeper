#include "CoordinateAnalysis.hpp"
#include <cctype>

namespace ms {
  InputAnalysis::Input CoordinateInput::check(const std::string& inp) const {
    if (inp.size() < 2 || !std::isalpha(inp[0])) {
      return InvalidIn {};
    }
    int x = std::toupper(inp[0]) - 'A';
    try {
      std::string sws = inp;
      int y = std::stoi(sws.erase(0, 1)) - 1;
      return CoordinateIn {x, y};
    }
    catch (...) {
      return IvalidIn {};
    }
  }
}
