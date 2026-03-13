#include "CoordinateAnalysis.hpp"
#include <cctype>

namespace ms {
  InputAnalysis::Input CoordinateAnalysis::check(const std::string& inp) const {
    std::string sws = inp;
    bool flag = false;

    if (sws.size() < 2 || !std::isalpha(sws[0])) {
      return InvalidIn {};
    }
    if (sws.size() > 3 && (sws[0] == 'f' || sws[0] == 'F') && sws[1] == ' ') {
        flag = true;
        sws.erase(0, 2);
    }
    int x = std::toupper(sws[0]) - 'A';
    try {
      int y = std::stoi(sws.erase(0, 1)) - 1;
      return CoordinateIn {x, y, flag};
    }
    catch (...) {
      return InvalidIn {};
    }
  }
}
