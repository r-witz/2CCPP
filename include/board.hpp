#ifndef BOARD_HPP
#define BOARD_HPP

#include "tile.hpp"
#include "player.hpp"

#include <vector>
#include <memory>

enum class display_mode { NORMAL, PLACING, SELECTION };
enum cell_state { EMPTY, P1, P2, P3, P4, P5, P6, P7, P8, P9, BONUS, STONE_CELL };

class Board {
protected:
    int size;
    std::vector<std::vector<cell_state>> board;
    std::vector<std::vector<std::shared_ptr<Tile>>> tileMapping;
    std::vector<std::shared_ptr<Player>> players;

    std::string convertForegroundToBackground(const std::string& colorCode);
    bool isBonusCell(cell_state state) const;
    int getClaimingPlayerId(int row, int col) const;
    bool isTouchingPlayerTile(int boardRow, int boardCol, int ownerId, bool samePlayer);

public:
    Board();
    Board(int number_player, std::vector<std::shared_ptr<Player>> players);

    int getSize();

    void displayBoard(display_mode mode=display_mode::NORMAL, int row=-1, int col=-1,
                      int current_player=-1, std::shared_ptr<Tile> placingTile=nullptr, bool canPlace=false);
    bool verifyBonusPlace(int x, int y);
    void placeBonus(int number_player);

    void claimSurroundedBonuses();
    bool canPlaceTile(std::shared_ptr<Tile> tile, int row, int col, bool firstRound, bool bonusTilePlacement=false);
    void placeTile(std::shared_ptr<Tile> tile, int row, int col, cell_state cell_type=EMPTY);
    void removeTile(std::shared_ptr<Tile> tileToRemove);
    std::shared_ptr<Tile> getTileAt(int row, int col);
    cell_state getCellAt(int row, int col);
    bool isStoneOnBoard();
    std::shared_ptr<Player> determineWinner();
};

#endif
