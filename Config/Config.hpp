#pragma once

namespace ms {

class Config {
public:
    Config() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMines() const { return mines; }
private:
    int width = 10;
    int height = 10;
    int mines = 10;
};
}