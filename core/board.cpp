#include "board.hpp"
#include <random>
#include <stack>

namespace ms {

Board::Board(int width, int height, int totalMines)
    : width_(width), height_(height), total_mines_(totalMines) {
    if (total_mines_ >= width_ * height_) {
        throw BoardException("Too many mines for the board size");
    }

    grid_.reserve(height_);
    for (int y = 0; y < height_; ++y) {
        auto& row = grid_.emplace_back();
        row.reserve(width_);
        for (int x = 0; x < width_; ++x) {
            row.push_back(std::make_unique<Cell>());
        }
    }
}

std::optional<std::reference_wrapper<Cell>> Board::getCell(int x, int y) {
    if (!isValidCoord(x, y)) {
        return std::nullopt;
    }
    return *grid_[y][x];
}

std::optional<std::reference_wrapper<const Cell>> Board::getCell(int x, int y) const {
    if (!isValidCoord(x, y)) {
        return std::nullopt;
    }
    return *grid_[y][x];
}

void Board::reset() {
    game_over_ = false;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            grid_[y][x]->reset();
        }
    }
}

bool Board::openCell(int x, int y) {
    auto cell_opt = getCell(x, y);
    if (!cell_opt) {
        return false;
    }

    Cell& cell = cell_opt->get();

    if (game_over_ || cell.getState() != CellState::Closed) {
        return false;
    }

    cell.open();

    if (cell.isMine()) {
        game_over_ = true;
        return false;
    }

    if (cell.getAdjacentMines() == 0) {
        expandEmptyRegion(x, y);
    }

    return true;
}

void Board::expandEmptyRegion(int startX, int startY) {
    std::stack<std::pair<int, int>> stack;
    stack.push({startX, startY});

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;

                int nx = x + dx;
                int ny = y + dy;

                auto neighbor_opt = getCell(nx, ny);
                if (!neighbor_opt) continue;

                Cell& neighbor = neighbor_opt->get();

                if (neighbor.getState() == CellState::Closed && !neighbor.isMine()) {
                    neighbor.open();

                    if (neighbor.getAdjacentMines() == 0) {
                        stack.push({nx, ny});
                    }
                }
            }
        }
    }
}

void Board::toggleFlag(int x, int y) {
    auto cell_opt = getCell(x, y);
    if (!cell_opt || game_over_) {
        return;
    }

    Cell& cell = cell_opt->get();
    cell.toggleFlag();
}

bool Board::isWin() const noexcept {
    if (game_over_) return false;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const Cell& cell = *grid_[y][x];
            if (cell.isMine() && cell.getState() != CellState::Flagged) {
                return false;
            }
            if (!cell.isMine() && cell.getState() != CellState::Opened) {
                return false;
            }
        }
    }
    return true;
}

}
