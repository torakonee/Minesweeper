#include <gtest/gtest.h>
#include "core/board.hpp"

using namespace ms;

TEST(BoardTest, ConstructorValid) {
    Board board(10, 10, 10);
    EXPECT_EQ(board.getWidth(), 10);
    EXPECT_EQ(board.getHeight(), 10);
    EXPECT_EQ(board.getTotalMines(), 10);
    EXPECT_FALSE(board.isGameOver());
}

TEST(BoardTest, ConstructorTooManyMines) {
    EXPECT_THROW(Board(5, 5, 26), BoardException);
    EXPECT_THROW(Board(5, 5, 100), BoardException);
}

TEST(BoardTest, ConstructorEdgeCases) {
    EXPECT_NO_THROW(Board(1, 1, 0));
    EXPECT_NO_THROW(Board(5, 5, 24));
    EXPECT_THROW(Board(5, 5, 25), BoardException);
}

TEST(BoardTest, GetCellValid) {
    Board board(5, 5, 5);
    auto cell = board.getCell(2, 2);
    EXPECT_TRUE(cell.has_value());
    EXPECT_EQ(cell->get().getState(), CellState::Closed);
}

TEST(BoardTest, GetCellInvalid) {
    Board board(5, 5, 5);
    EXPECT_FALSE(board.getCell(-1, 0).has_value());
    EXPECT_FALSE(board.getCell(0, -1).has_value());
    EXPECT_FALSE(board.getCell(5, 0).has_value());
    EXPECT_FALSE(board.getCell(0, 5).has_value());
    EXPECT_FALSE(board.getCell(5, 5).has_value());
}

TEST(BoardTest, GetCellConstVersion) {
    const Board board(5, 5, 5);
    auto cell = board.getCell(2, 2);
    EXPECT_TRUE(cell.has_value());
    EXPECT_EQ(cell->get().getState(), CellState::Closed);
}

TEST(BoardTest, OpenCellValid) {
    Board board(5, 5, 5);
    EXPECT_TRUE(board.openCell(2, 2));
    auto cell = board.getCell(2, 2);
    EXPECT_EQ(cell->get().getState(), CellState::Opened);
}

TEST(BoardTest, OpenCellInvalidCoordinates) {
    Board board(5, 5, 5);
    EXPECT_FALSE(board.openCell(-1, 0));
    EXPECT_FALSE(board.openCell(5, 5));
}

TEST(BoardTest, OpenCellTwice) {
    Board board(5, 5, 5);
    EXPECT_TRUE(board.openCell(2, 2));
    EXPECT_FALSE(board.openCell(2, 2));
}

TEST(BoardTest, ToggleFlag) {
    Board board(5, 5, 5);
    board.toggleFlag(2, 2);
    auto cell = board.getCell(2, 2);
    EXPECT_EQ(cell->get().getState(), CellState::Flagged);
    board.toggleFlag(2, 2);
    EXPECT_EQ(cell->get().getState(), CellState::Closed);
}

TEST(BoardTest, ToggleFlagInvalidCoordinates) {
    Board board(5, 5, 5);
    board.toggleFlag(-1, 0);
    board.toggleFlag(5, 5);
    SUCCEED();
}

TEST(BoardTest, CannotFlagOpenedCell) {
    Board board(5, 5, 5);
    board.openCell(2, 2);
    board.toggleFlag(2, 2);
    auto cell = board.getCell(2, 2);
    EXPECT_EQ(cell->get().getState(), CellState::Opened);
}

TEST(BoardTest, WinConditionNotMet) {
    Board board(3, 3, 1);
    EXPECT_FALSE(board.isWin());
}

TEST(BoardTest, Reset) {
    Board board(5, 5, 5);
    board.openCell(2, 2);
    board.toggleFlag(3, 3);
    board.reset();
    EXPECT_FALSE(board.isGameOver());
    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            auto cell = board.getCell(x, y);
            EXPECT_EQ(cell->get().getState(), CellState::Closed);
            EXPECT_FALSE(cell->get().isMine());
            EXPECT_EQ(cell->get().getAdjacentMines(), 0);
        }
    }
}
