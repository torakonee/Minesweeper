#include <gtest/gtest.h>
#include "core/cell.hpp"

using namespace ms;

TEST(CellTest, DefaultState) {
    Cell cell;
    EXPECT_EQ(cell.getState(), CellState::Closed);
    EXPECT_FALSE(cell.isMine());
    EXPECT_EQ(cell.getAdjacentMines(), 0);
}

TEST(CellTest, OpenCell) {
    Cell cell;
    EXPECT_TRUE(cell.open());
    EXPECT_EQ(cell.getState(), CellState::Opened);
    EXPECT_FALSE(cell.open());
    EXPECT_EQ(cell.getState(), CellState::Opened);
}

TEST(CellTest, ToggleFlag) {
    Cell cell;
    EXPECT_TRUE(cell.toggleFlag());
    EXPECT_EQ(cell.getState(), CellState::Flagged);
    cell.open();
    EXPECT_FALSE(cell.toggleFlag());
    EXPECT_EQ(cell.getState(), CellState::Opened);
}

TEST(CellTest, SetMine) {
    Cell cell;
    cell.setMine(true);
    EXPECT_TRUE(cell.isMine());
    cell.setMine(false);
    EXPECT_FALSE(cell.isMine());
}

TEST(CellTest, SetAdjacentMines) {
    Cell cell;
    cell.setAdjacentMines(5);
    EXPECT_EQ(cell.getAdjacentMines(), 5);
    cell.setAdjacentMines(0);
    EXPECT_EQ(cell.getAdjacentMines(), 0);
    cell.setAdjacentMines(8);
    EXPECT_EQ(cell.getAdjacentMines(), 8);
}

TEST(CellTest, Reset) {
    Cell cell;
    cell.setMine(true);
    cell.setAdjacentMines(3);
    cell.open();
    cell.reset();
    EXPECT_EQ(cell.getState(), CellState::Closed);
    EXPECT_FALSE(cell.isMine());
    EXPECT_EQ(cell.getAdjacentMines(), 0);
}

TEST(CellTest, FlagThenOpen) {
    Cell cell;
    cell.toggleFlag();
    EXPECT_EQ(cell.getState(), CellState::Flagged);
    EXPECT_FALSE(cell.open());
    EXPECT_EQ(cell.getState(), CellState::Flagged);
}

TEST(CellTest, ConstexprGetters) {
    constexpr Cell cell;
    static_assert(cell.getState() == CellState::Closed);
    static_assert(!cell.isMine());
    static_assert(cell.getAdjacentMines() == 0);
}