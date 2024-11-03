#include "../include/board.hpp"
#include <iostream>


Board::Board() {
    board = std::vector<std::vector<board_case>>(30, std::vector<board_case>(30, EMPTY));
}


void Board::displayBoard(bool isPlayer) {


    if (isPlayer) { 
    std::cout << "+";
    for (int col = 0; col < 30; ++col) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl; 
    for (int row = 0; row < 30; ++row) {
        std::cout << "|";
        for (int col = 0; col < 30; ++col) {
            if (board[row][col] == EMPTY) { 
                std::cout << "  ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
    for (int col = 0; col < 30; ++col) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl;
    
    } else {
        std::cout << "+";
        for (int col = 0; col < 20; ++col) {
            std::cout << "--";
        }
        std::cout << "+" << std::endl; 
        for (int row = 0; row < 20; ++row) {
            std::cout << "|";
            for (int col = 0; col < 20; ++col) {
                if (board[row][col] == EMPTY) { 
                    std::cout << "  ";
                } else {
                    std::cout << "  ";
                }
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "+";
        for (int col = 0; col < 20; ++col) {
            std::cout << "--";
        }
        std::cout << "+" << std::endl;
    }
}