#ifndef BOARD_HPP
#define BOARD_HPP

#include "tile.hpp"
#include "player.hpp"

#include <vector>
#include <memory>

enum cell_state {EMPTY, P1, P2, P3, P4, P5, P6, P7, P8, P9, TILE_EXCHANGE, STONE, ROBBERY};

class Board {
protected:
    int size;
    std::vector<std::vector<cell_state>> board;
    std::vector<std::vector<std::shared_ptr<Tile>>> tileMapping;
    std::vector<std::shared_ptr<Player>> players;

    bool isTouchingPlayerTile(int boardRow, int boardCol, int ownerId, bool samePlayer);

public:
    Board();
    Board(int number_player, std::vector<std::shared_ptr<Player>> players);

    int getSize();

    void displayBoard(std::shared_ptr<Tile> previewTile=nullptr, int previewRow=-1, int previewCol=-1, int currentPlayer=-1, bool canPlace=false);
    bool verifyBonusPlace(int x, int y);
    void placeBonus(int number_player);

    bool canPlaceTile(std::shared_ptr<Tile> tile, int row, int col, bool firstRound);
    void placeTile(std::shared_ptr<Tile> tile, int row, int col);
    std::shared_ptr<Tile> getTileAt(int x, int y);
};

#endif
