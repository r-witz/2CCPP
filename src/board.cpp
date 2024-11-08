#include "../include/board.hpp"
#include <iostream>
#include <cmath>
#include <random>

Board::Board() {
    size = 30;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
    tileMapping = std::vector<std::vector<Tile*>>(size, std::vector<Tile*>(size, nullptr));
}

Board::Board(int number_player, std::vector<Player> &players) {
    size = number_player > 4 ? 30 : 20;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
    tileMapping = std::vector<std::vector<Tile*>>(size, std::vector<Tile*>(size, nullptr));
    this->players = players;
}

int Board::getSize() { return size; }

void Board::displayBoard(Tile* previewTile, int previewRow, int previewCol, int currentPlayer, bool canPlace) {
    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl;

    for (int i = 0; i < size; ++i) {
        std::cout << "|";
        for (int j = 0; j < size; ++j) {
            bool inPreview = false;
            if (previewTile == nullptr) { inPreview = false; }
            else {
                for (int x = 0; x < previewTile->getGrid().size(); ++x) {
                    for (int y = 0; y < previewTile->getGrid()[0].size(); ++y) {
                        if (previewTile->getGrid()[x][y] && i == previewRow + x && j == previewCol + y) { inPreview = true; }
                    }
                }

            }

            if (inPreview) { std::cout << (canPlace ? players[currentPlayer-1].getColor() : "\033[0m") << "██" << "\033[0m"; } 
            else {
                switch (board[i][j]) {
                    case cell_state::EMPTY: std::cout << "  "; break;
                    case cell_state::ROBBERY: std::cout << "\033[38;2;255;255;204m◖◗\033[0m"; break;
                    case cell_state::STONE: std::cout << "\033[38;2;192;192;192m◖◗\033[0m"; break;
                    case cell_state::TILE_EXCHANGE: std::cout << "\033[38;2;51;153;102m◖◗\033[0m"; break;
                    default:
                        int player_index = static_cast<int>(board[i][j]) - static_cast<int>(cell_state::P1);
                        std::string player_color = players[player_index].getColor();
                        std::cout << player_color << "██" << "\033[0m";
                }
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl << std::endl;
}

bool Board::verifyBonusPlace(int x, int y) {
    if (x <= 0 || x >= size - 1 || y <= 0 || y >= size - 1) {
        return false;
    }

    for (int row = -1; row <= 1; ++row) {
        for (int col = -1; col <= 1; ++col) {
            if (row == 0 && col == 0) {
                continue;
            }

            int rowx = x + row;
            int coly = y + col;

            if (rowx >= 0 && rowx < size && coly >= 0 && coly < size) {
                if (board[rowx][coly] == cell_state::ROBBERY ||
                    board[rowx][coly] == cell_state::STONE ||
                    board[rowx][coly] == cell_state::TILE_EXCHANGE) {
                    return false;
                }
            }
        }
    }

    return true;
}

void Board::placeBonus(int number_player) {
    int number_tile_exchange = static_cast<int>(std::round(1.5 * number_player));
    int number_stone = static_cast<int>(std::round(0.5 * number_player));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, size - 1);

    for (int i = 0; i < number_player; ++i) {
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (!verifyBonusPlace(x, y));

        board[x][y] = cell_state::ROBBERY;
    }

    for (int i = 0; i < number_stone; ++i) {
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (!verifyBonusPlace(x, y));

        board[x][y] = cell_state::STONE;
    }

    for (int i = 0; i < number_tile_exchange; ++i) {
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (!verifyBonusPlace(x, y));

        board[x][y] = cell_state::TILE_EXCHANGE;
    }
}

bool Board::isTouchingSamePlayerTile(int boardRow, int boardCol, int ownerId) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int neighborRow = boardRow + dx;
            int neighborCol = boardCol + dy;

            if (!(neighborRow >= 0 && neighborRow < size && neighborCol >= 0 && neighborCol < size)) { return false; }
            if (tileMapping[neighborRow][neighborCol] && tileMapping[neighborRow][neighborCol]->getOwnerId() == ownerId) { return true; }
        }
    }

    return false;
}

bool Board::canPlaceTile(Tile* tile, int row, int col, bool firstRound) {
    std::vector<std::vector<bool>> tileGrid = tile->getGrid();
    int ownerId = tile->getOwnerId();
    bool touchesSamePlayerTile = false;

    for (int i = 0; i < tileGrid.size(); ++i) {
        for (int j = 0; j < tileGrid[i].size(); ++j) {
            if (!tileGrid[i][j]) { continue; }
            int boardRow = row + i;
            int boardCol = col + j;

            if (boardRow < 0 || boardRow >= size || boardCol < 0 || boardCol >= size) { return false; }
            if (board[boardRow][boardCol] != cell_state::EMPTY) { return false; }

            if (!firstRound) { touchesSamePlayerTile = isTouchingSamePlayerTile(boardRow, boardCol, ownerId); }
        }
    }

    return firstRound || touchesSamePlayerTile;
}

void Board::placeTile(Tile *tile, int row, int col) {
    for (int i=0; i < tile->getGrid().size(); i++) {
        for (int j=0; j < tile->getGrid()[0].size(); j++) {
            if (tile->getGrid()[i][j]) {
                board[row+i][col+j] = static_cast<cell_state>(tile->getOwnerId());
                tileMapping[row+i][col+j] = tile;
            }
        }
    }
}

Tile* Board::getTileAt(int row, int col) {
    return tileMapping[row][col];
}
