#include "ConfigAnalysis.hpp"
#include <sstream>

namespace ms {
InputAnalysis::Input ConfigAnalysis::check(const std::string& inp) const {
    if (inp == "easy" || inp == "Easy") {
        return InputAnalysis::DifficultyIn {InputAnalysis::Difficulty::Easy};
    }
    if (inp == "normal" || inp == "Normal") {
        return InputAnalysis::DifficultyIn {InputAnalysis::Difficulty::Normal};
    }
    if (inp == "hard" || inp == "Hard") {
        return InputAnalysis::DifficultyIn {InputAnalysis::Difficulty::Hard};
    }

    int sz = 0;
    std::stringstream st(inp);
    if (ss >> sz && sz > 0) {
        return InputAnalysis::SizeIn {sz, sz};
    }

    return InputAnalysis::InvalidIn{};
}
}
