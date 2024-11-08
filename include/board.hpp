#ifndef BOARD_HPP
#define BOARD_HPP

#include "tile.hpp"
#include "player.hpp"

#include <vector>

enum cell_state {EMPTY, P1, P2, P3, P4, P5, P6, P7, P8, P9, TILE_EXCHANGE, STONE, ROBBERY};

class Board {
protected:
    int size;
    std::vector<std::vector<cell_state>> board;
    std::vector<std::vector<Tile*>> tileMapping;
    std::vector<Player> players;

public:
    Board();
    Board(int number_player, std::vector<Player> &players);

    void displayBoard();
    bool verifyBonusPlace(int x, int y);
    void placeBonus(int number_player);

    void placeTile(Tile *tile, int row, int col);
    Tile* getTileAt(int x, int y);
};

#endif
