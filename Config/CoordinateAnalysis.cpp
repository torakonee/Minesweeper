#include "CoordinateAnalysis.hpp"
#include <cctype>

namespace ms {
  InputAnalysis::Input CoordinateInput::check(const std::string& inp) const {
    if (inp.size() < 2 || !std::isalpha(inp[0])) {
      return InvalidIn {};
    }
    bool flag = false;
    if (inp.size() > 3 && (inp[0] == 'f' || inp[0] == 'F') && inp[1] == ' ') {
        flag = true;
        sws.erase(0, 2);
    }
    int x = std::toupper(inp[0]) - 'A';
    try {
      std::string sws = inp;
      int y = std::stoi(sws.erase(0, 1)) - 1;
      return CoordinateIn {x, y, flag};
    }
    catch (...) {
      return InvalidIn {};
    }
  }
}
