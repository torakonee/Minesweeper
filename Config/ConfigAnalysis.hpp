#pragma once
#include "InputAnalysis.hpp"

namespace ms {
class ConfigAnalysis : public InputAnalysis {
public:
  Input check(const std::string& inp) const override;
};
}
