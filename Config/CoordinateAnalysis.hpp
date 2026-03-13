#pragma once
#include "InputAnalysis.hpp"

namespace ms {
class CoordinateAnalysis : public InputAnalysis {
public:
  Input check(const std::string& inp) const override;
};
}
