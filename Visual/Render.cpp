#include "Render.hpp"
#include <iostream>

namespace ms{
    void Render::drawField(const Board& board) const {
        std::cout << "  ";
        for (int x = 0; x < board.getWidth(); ++x) {
            std::cout << x << " ";
        }
        std::cout << '\n';
        for (int y = 0; y < board.getHeight(); ++y) {
            std::cout << y << " ";
            for (int x = 0; x < board.getWidth(); ++x) {
                auto cell_opt = board.getCell(x, y);

                if (!cell_opt) {
                    std::cout << "? ";
                    continue;
                }

                const Cell& cell = cell_opt->get();

                if (cell.getState() == CellState::Closed) {
                    std::cout << "■ ";
                } else if (cell.getState() == CellState::Flagged) {
                    std::cout << "⚑ ";
                } else if (cell.isMine()) {
                    std::cout << "* ";
                } else if (cell.getAdjacentMines() == 0) {
                    std::cout << "□ ";
                } else {
                    std::cout << static_cast<int>(cell.getAdjacentMines()) << " ";
                }
            }
            std::cout << '\n';
        }
    }
}