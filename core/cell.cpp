#include "cell.hpp"

namespace ms {

bool Cell::open() {
    if (state_ != CellState::Closed) {
        return false;
    }
    state_ = CellState::Opened;
    return true;
}

bool Cell::toggleFlag() {
    if (state_ != CellState::Closed) {
        return false;
    }
    state_ = CellState::Flagged;
    return true;
}

void Cell::reset() noexcept {
    state_ = CellState::Closed;
    is_mine_ = false;
    adjacent_mines_ = 0;
}

}
