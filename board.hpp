#pragma once
#include "cell.hpp"
#include <vector>
#include <memory>
#include <optional>
#include <functional>
#include <stdexcept>

namespace ms {

class BoardException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Board {
public:
    Board(int width, int height, int totalMines);

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = default;
    Board& operator=(Board&&) = default;

    [[nodiscard]] int getWidth() const noexcept { return width_; }
    [[nodiscard]] int getHeight() const noexcept { return height_; }
    [[nodiscard]] int getTotalMines() const noexcept { return total_mines_; }

    [[nodiscard]] std::optional<std::reference_wrapper<Cell>> getCell(int x, int y);
    [[nodiscard]] std::optional<std::reference_wrapper<const Cell>> getCell(int x, int y) const;

    bool openCell(int x, int y);
    void toggleFlag(int x, int y);
    [[nodiscard]] bool isGameOver() const noexcept { return game_over_; }
    [[nodiscard]] bool isWin() const noexcept;
    void reset();

private:
    [[nodiscard]] constexpr bool isValidCoord(int x, int y) const noexcept {
        return x >= 0 && x < width_ && y >= 0 && y < height_;
    }

    void generateMines(int firstX, int firstY);
    void calculateAdjacentCounts();
    void expandEmptyRegion(int x, int y);

    int width_;
    int height_;
    int total_mines_;
    bool game_over_ = false;
    bool mines_generated_ = false;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid_;
};

}
