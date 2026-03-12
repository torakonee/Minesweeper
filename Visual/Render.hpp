#pragma once
#include "../core/board.hpp"
#include "../Config/Config.cpp"

namespace ms {

class Render{
public:
    void drawField(const Board& board) const;
};
}