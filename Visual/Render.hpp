#pragma once
#include "../core/board.hpp"
#include "../Config/Config.hpp"

namespace ms {

class Render{
public:
    void drawField(const Board& board) const;
};
}
