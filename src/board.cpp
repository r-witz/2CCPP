#include "../include/board.hpp"
#include <iostream>


Board::Board() {
    size = 30;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
}

Board::Board(int number_player) {
    size = number_player > 4 ? 30 : 20;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
}

void Board::displayBoard() {
    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl;

    for (int i = 0; i < size; ++i) {
        std::cout << "|";
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == cell_state::EMPTY) {
                std::cout << "  ";
            } else {
                std::cout << "██";
            }
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl << std::endl;
}

