#include "../include/tile_manager.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

TileManager::TileManager() {
    allTiles = readTileFile("data/tiles.txt");
}

std::vector<std::shared_ptr<Tile>> TileManager::readTileFile(const std::string filePath) {
    std::ifstream file(filePath);
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::vector<bool>> currentTileGrid;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            std::shared_ptr<Tile> tilePtr = std::make_shared<Tile>(currentTileGrid);
            tiles.push_back(tilePtr);
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

void TileManager::clearLines(int numLines) const {
    for (int i = 0; i < numLines; ++i) {
        std::cout << "\033[F" << "\033[K";
    }
}

void TileManager::displayTiles(int number_of_tile, int offset, int selected_tile, std::string selectedTileColor) {
    int endIndex = offset + number_of_tile;

    int maxRows = 0;
    for (int i = offset; i < endIndex; ++i) {
        if (i < tileQueue.size()) { maxRows = std::max(maxRows, static_cast<int>(tileQueue[i]->getGrid().size())); }
    }

    for (int row = 0; row < maxRows; ++row) {
        for (int i = offset; i < endIndex; ++i) {
            if (i >= tileQueue.size()) { continue; }

            const auto& grid = tileQueue[i]->getGrid();

            if (row < grid.size()) {
                if (i == selected_tile) {
                    std::cout << selectedTileColor;
                    for (bool cell : grid[row]) { std::cout << (cell ? "██" : "  "); }
                    std::cout << "\033[0m";
                } else { for (bool cell : grid[row]) { std::cout << (cell ? "██" : "  "); } }
            } else if (!grid.empty()) { std::cout << std::string(grid[0].size() * 2, ' '); }

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

    for (int i = 0; i < totalTiles; ++i) {
        std::shared_ptr<Tile> tilePtr = allTiles[i];
        tileQueue.push_back(tilePtr);
    }
}

std::shared_ptr<Tile> TileManager::getNextTile() {
    std::shared_ptr<Tile> nextTile = tileQueue[0];
    tileQueue.erase(tileQueue.begin());
    return nextTile;
}

std::shared_ptr<Tile> TileManager::chooseTile(std::string selectedTileColor) {
    int offset = 1;
    int number_of_tiles = std::min(5, static_cast<int>(tileQueue.size()) - offset);
    if (number_of_tiles <= 0) { throw std::runtime_error("No tiles left to choose from!"); }
    int selected_tile = offset;
    inputs input;

    int maxRows = 0;
    for (int i = offset; i < offset+number_of_tiles; ++i) {
        maxRows = std::max(maxRows, static_cast<int>(tileQueue[i]->getGrid().size()));
    }

    do {
        std::cout << "Choose a tile :" << std::endl;
        displayTiles(number_of_tiles, offset, selected_tile, selectedTileColor);
        input = input_handler.getKeyPress();

        if (input == inputs::RIGHT) { if (++selected_tile >= offset + number_of_tiles) { selected_tile = offset; } }
        else if (input == inputs::LEFT) { if (--selected_tile < offset) { selected_tile = offset + number_of_tiles - 1; } }

        if (input != inputs::ENTER) { clearLines(maxRows+2); }
    } while (input != inputs::ENTER);

    std::shared_ptr<Tile> chosenTile = tileQueue[selected_tile];
    std::vector<std::shared_ptr<Tile>> newQueue;
    for (int i = selected_tile + 1; i < tileQueue.size(); ++i) { newQueue.push_back(tileQueue[i]); }
    for (int i = 0; i < selected_tile; ++i) { newQueue.push_back(tileQueue[i]); }
    tileQueue = newQueue;

    return chosenTile;
}
