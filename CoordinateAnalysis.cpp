#include "CoordinateAnalysis.hpp"
#include <cctype>

namespace ms {
  InputAnalysis::Input CoordinateAnalysis::check(const std::string& inp) const {
    std::string sws = inp;
    bool flag = false;
    if (inp.size() > 3 && (inp[0] == 'f' || inp[0] == 'F') && inp[1] == ' ') {
        flag = true;
        sws.erase(0, 2);
    }
    if (sws.size() < 2 || !std::isalpha(sws[0])) {
      return InputAnalysis::InvalidIn {};
    }
    int x = std::toupper(sws[0]) - 'A';
    try {
      int y = std::stoi(sws.erase(0, 1)) - 1;
      return InputAnalysis::CoordinateIn {x, y, flag};
    }
    catch (...) {
      return InputAnalysis::InvalidIn {};
    }
  }
}
