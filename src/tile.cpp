#include "../include/tile.hpp"

#include <algorithm>
#include <iostream>

Tile::Tile() {
    this->grid = std::vector<std::vector<bool>>(1, std::vector<bool>(1, true));
    this->owner_id = -1;
}

Tile::Tile(const std::vector<std::vector<bool>> &grid, int owner_id, int cluster_id) {
    this->grid = grid;
    this->owner_id = owner_id;
}

std::vector<std::vector<bool>> Tile::getGrid() { return grid; }

int Tile::getOwnerId() { return owner_id; }
void Tile::setOwnerId(int id) { owner_id = id; }

void Tile::flip() {
    std::reverse(grid.begin(), grid.end());
}

void Tile::rotate() {
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> rotatedGrid(cols, std::vector<bool>(rows));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            rotatedGrid[c][rows - r - 1] = grid[r][c];
        }
    }

    grid = rotatedGrid;
}

void Tile::display() {
    for (const auto& row : grid) {
        for (bool cell : row) { std::cout << (cell ? "██" : "  "); }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
