#include "../include/tile_manager.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

TileManager::TileManager() {
    allTiles = readTileFile("data/tiles.txt");
}

std::vector<Tile> TileManager::readTileFile(const std::string filePath) {
    std::ifstream file(filePath);
    std::vector<Tile> tiles;
    std::vector<std::vector<bool>> currentTileGrid;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            tiles.push_back(Tile(currentTileGrid));
            currentTileGrid.clear();
        } else {
            std::vector<bool> row;
            for (char c : line) {
                row.push_back(c == '1');
            }
            currentTileGrid.push_back(row);
        }
    }

    file.close();
    return tiles;
}

void TileManager::displayTiles(int number_of_tile, int offset, int selected_tile, std::string selectedTileColor) {
    int endIndex = offset + number_of_tile;

    int maxRows = 0;
    for (int i = offset; i < endIndex; ++i) {
        maxRows = std::max(maxRows, static_cast<int>(tileQueue[i].getGrid().size()));
    }

    for (int row = 0; row < maxRows; ++row) {
        for (int i = offset; i < endIndex; ++i) {
            const auto& grid = tileQueue[i].getGrid();

            if (row < grid.size()) {
                if (i == selected_tile) {
                    std::cout << selectedTileColor;
                    for (bool cell : grid[row]) { std::cout << (cell ? "██" : "  "); }
                    std::cout << "\033[0m";
                } else {
                    for (bool cell : grid[row]) { std::cout << (cell ? "██" : "  "); }
                }
            } else { std::cout << std::string(grid[0].size() * 2, ' '); }

            std::cout << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void TileManager::randomizeTileQueue(int player_number) {
    int totalTiles = static_cast<int>(std::round(10.67 * player_number));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allTiles.begin(), allTiles.end(), gen);

    tileQueue.insert(tileQueue.end(), allTiles.begin(), allTiles.begin() + totalTiles);
}

Tile TileManager::getNextTile() {
    Tile nextTile = tileQueue[0];
    tileQueue.erase(tileQueue.begin());
    return nextTile;
}

Tile TileManager::chooseTile() {
    int offset = 1;
    int number_of_tiles = 5;
    int selected_tile = offset;
    inputs input;

    do {
        std::cout << "Choose a tile :" << std::endl;
        displayTiles(number_of_tiles, offset, selected_tile, "\033[38;2;255;0;0m");
        input = input_handler.getKeyPress();

        if (input == inputs::RIGHT) { if (++selected_tile >= offset + number_of_tiles) { selected_tile = offset; } }
        else if (input == inputs::LEFT) { if (--selected_tile < offset) { selected_tile = offset + number_of_tiles - 1; } }
    } while (input != inputs::ENTER);

    Tile chosenTile = tileQueue[selected_tile];
    std::rotate(tileQueue.begin(), tileQueue.begin() + selected_tile - 1, tileQueue.end());
    tileQueue.erase(tileQueue.begin());

    return chosenTile;
}
