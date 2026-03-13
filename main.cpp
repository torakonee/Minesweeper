#include "core/board.hpp"
#include "Visual/Render.hpp"
#include "Config/Config.hpp"

int main() {
    ms::Config config;

    ms::Board board(
        config.getWidth(),
        config.getHeight(),
        config.getMines()
    );

    ms::Render render;

    render.drawField(board);

    return 0;
}