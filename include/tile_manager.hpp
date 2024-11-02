#ifndef TILES_HPP
#define TILES_HPP

#include "input_handler.hpp"
#include "tile.hpp"

#include <string>
#include <vector>

class TileManager {
private:
    InputHandler input_handler;
    std::vector<Tile> allTiles;
    std::vector<Tile> tileQueue;

    std::vector<Tile> readTileFile(const std::string filePath);

public:
    TileManager();

    void randomizeTileQueue(int player_number);
    Tile getNextTile();
    void displayTiles(int number_of_tile, int offset, int selected_tile, std::string selectedTileColor);
    Tile chooseTile();
};

#endif
