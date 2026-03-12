#pragma once
#include "../core/board.hpp"

namespace ms {

class Render{
public:
    void drawField(const Board& board) const;
};
}