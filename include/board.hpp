#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

enum board_case {EMPTY, P1, P2, P3, P4, P5, P6, P7, P8, P9, TILE_EXCHANGE, STONE, ROBBERY};

class Board {
protected:
    std::vector<std::vector<board_case>> board;

public:
    Board();
    void displayBoard(bool isPlayer);
};

#endif