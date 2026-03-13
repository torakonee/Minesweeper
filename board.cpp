#include "board.hpp"
#include <random>
#include <stack>

namespace ms {

Board::Board(int width, int height, int totalMines)
    : width_(width), height_(height), total_mines_(totalMines), mines_generated_(false) {
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

void Board::generateMines(int firstX, int firstY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, width_ - 1);
    std::uniform_int_distribution<> distY(0, height_ - 1);
    
    int minesPlaced = 0;
    
    while (minesPlaced < total_mines_) {
        int x = distX(gen);
        int y = distY(gen);
        
        if (x == firstX && y == firstY) continue;
        
        Cell& cell = *grid_[y][x];
        
        if (!cell.isMine()) {
            cell.setMine(true);
            minesPlaced++;
        }
    }
    
    calculateAdjacentCounts();
    mines_generated_ = true;
}

void Board::calculateAdjacentCounts() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (grid_[y][x]->isMine()) continue;
            
            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    if (isValidCoord(nx, ny) && grid_[ny][nx]->isMine()) {
                        count++;
                    }
                }
            }
            grid_[y][x]->setAdjacentMines(count);
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

    if (!mines_generated_) {
        generateMines(x, y);
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

    if (!mines_generated_) {
        generateMines(x, y);
    }

    Cell& cell = cell_opt->get();
    cell.toggleFlag();
}

bool Board::isWin() const noexcept {
    if (game_over_) return false;
    if (!mines_generated_) return false;

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

void Board::reset() {
    game_over_ = false;
    mines_generated_ = false;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            grid_[y][x]->reset();
        }
    }
}

}
