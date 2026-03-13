cmake_minimum_required(VERSION 3.20)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 23)

include_directories(core)
include_directories(Visual)

add_executable(Minesweeper
        core/board.cpp
        core/cell.cpp
        Visual/Render.cpp
        Config/Config.cpp
        Config/ConfigAnalysis.cpp
        Config/CoordinateAnalysis.cpp
        core/Status.cpp
        main.cpp
)
