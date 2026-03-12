cmake_minimum_required(VERSION 4.0)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 23)

include_directories(core)
include_directories(Visual)

add_executable(Minesweeper
        core/board.cpp
        core/cell.cpp
        Visual/Render.cpp
)
