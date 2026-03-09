#pragma once
#include <cstdint>

namespace ms {

enum class CellState : std::uint8_t {
    Closed,
    Opened,
    Flagged
};

class Cell {
public:
    constexpr Cell() = default;

    [[nodiscard]] constexpr CellState getState() const noexcept { return state_; }
    [[nodiscard]] constexpr bool isMine() const noexcept { return is_mine_; }
    [[nodiscard]] constexpr std::uint8_t getAdjacentMines() const noexcept { return adjacent_mines_; }

    void setMine(bool is_mine = true) noexcept { is_mine_ = is_mine; }
    void setAdjacentMines(std::uint8_t count) noexcept { adjacent_mines_ = count; }

    bool open();
    bool toggleFlag();
    void reset() noexcept;

private:
    CellState state_ = CellState::Closed;
    bool is_mine_ = false;
    std::uint8_t adjacent_mines_ = 0;
};

} 
