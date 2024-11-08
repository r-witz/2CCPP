#ifndef TILES_HPP
#define TILES_HPP

#include "input_handler.hpp"
#include "tile.hpp"

#include <string>
#include <vector>
#include <memory>

class TileManager {
private:
    InputHandler input_handler;
    std::vector<std::shared_ptr<Tile>> allTiles;
    std::vector<std::shared_ptr<Tile>> tileQueue;

    std::vector<std::shared_ptr<Tile>> readTileFile(const std::string filePath);

public:
    TileManager();

    void randomizeTileQueue(int player_number);
    void displayTiles(int number_of_tile, int offset, int selected_tile, std::string selectedTileColor);
    std::shared_ptr<Tile> getNextTile();
    std::shared_ptr<Tile> chooseTile(std::string selectedTileColor);
};

#endif
