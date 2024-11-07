#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

class Tile {
private:
    std::vector<std::vector<bool>> grid;

public:
    Tile();
    Tile(const std::vector<std::vector<bool>> &grid);

    std::vector<std::vector<bool>> getGrid();
    void flip();
    void rotate();
    void display();
};

#endif
