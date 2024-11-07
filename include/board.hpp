#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

enum cell_state {EMPTY, P1, P2, P3, P4, P5, P6, P7, P8, P9, TILE_EXCHANGE, STONE, ROBBERY};

class Board {
protected:
    int size;
    std::vector<std::vector<cell_state>> board;

public:
    Board();
    Board(int number_player);

    void displayBoard();
    bool verifyBonusPlace(int x, int y);
    void placeBonus(int number_player);
};

#endif
