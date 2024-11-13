#include "../include/board.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>

Board::Board() {
    size = 30;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
    tileMapping = std::vector<std::vector<std::shared_ptr<Tile>>>(size, std::vector<std::shared_ptr<Tile>>(size, nullptr));
}

Board::Board(int number_player, std::vector<std::shared_ptr<Player>> players) {
    size = number_player > 4 ? 30 : 20;
    board = std::vector<std::vector<cell_state>>(size, std::vector<cell_state>(size, cell_state::EMPTY));
    tileMapping = std::vector<std::vector<std::shared_ptr<Tile>>>(size, std::vector<std::shared_ptr<Tile>>(size, nullptr));
    this->players = players;
}

int Board::getSize() { return size; }

void Board::displayBoard(display_mode mode, int row, int col, int current_player, std::shared_ptr<Tile> placingTile, bool canPlace) {

    const std::string robbery_color = "\033[38;2;255;255;204m";
    const std::string stone_color = "\033[38;2;192;192;192m";
    const std::string tile_exchange_color = "\033[38;2;51;153;102m";
    const std::string reset_color = "\033[0m";
    const std::string cursor_color = "\033[48;2;255;255;255m\033[38;2;255;255;255m";
    const std::string highlight_color = "\033[38;2;255;255;255m";

    std::shared_ptr<Tile> selectedTile = (mode == display_mode::SELECTION) ? tileMapping[row][col] : nullptr;
    bool highlightFullTile = selectedTile && selectedTile->getOwnerId()-1 != current_player;

    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl;

    for (int i = 0; i < size; ++i) {
        std::cout << "|";
        for (int j = 0; j < size; ++j) {
            std::shared_ptr<Tile> tile = tileMapping[i][j];
            int ownerId = tile ? tile->getOwnerId() : -1;
            bool inPreview = false;
            bool inSelection = (mode == display_mode::SELECTION && i == row && j == col);
            bool isPartOfSelectedTile = highlightFullTile && (tile == selectedTile);

            if (mode == display_mode::PLACING && placingTile != nullptr) {
                for (int x = 0; x < placingTile->getGrid().size(); ++x) {
                    for (int y = 0; y < placingTile->getGrid()[0].size(); ++y) {
                        if (placingTile->getGrid()[x][y] && i == row + x && j == col + y) { inPreview = true; }
                    }
                }
            }

            if (mode == display_mode::PLACING && inPreview) {
                std::cout << (canPlace ? players[current_player - 1]->getColor() : reset_color) << "██" << reset_color;
            } else if (mode == display_mode::SELECTION && (inSelection || isPartOfSelectedTile)) {
                std::cout << cursor_color << "██" << reset_color;
            } else {
                if (board[i][j] == cell_state::BONUS && tile) {
                    std::string owner_color = (ownerId > 0) ? players[ownerId - 1]->getColor() : reset_color;
                    std::string bonus_color;
                    switch (tile->getBonusState()) {
                        case bonus_state::ROBBERY: bonus_color = robbery_color; break;
                        case bonus_state::STONE: bonus_color = stone_color; break;
                        case bonus_state::TILE_EXCHANGE: bonus_color = tile_exchange_color; break;
                        default: bonus_color = reset_color; break;
                    }
                    std::cout << convertForegroundToBackground(owner_color) << bonus_color << "◢◣" << reset_color;
                }
                else if (board[i][j] == cell_state::EMPTY) { std::cout << "  "; }
                else if (board[i][j] == cell_state::STONE_CELL) {std::cout << stone_color << "██" << reset_color; }
                else {
                    std::string player_color = players[ownerId - 1]->getColor();
                    std::cout << player_color << "██" << reset_color;
                }
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+" << std::string(size * 2, '-') << "+" << std::endl << std::endl;
}

std::string Board::convertForegroundToBackground(const std::string& colorCode) {
    std::string newColorCode = colorCode;
    size_t pos = newColorCode.find("38;");
    if (pos != std::string::npos) { newColorCode.replace(pos, 2, "48"); }
    return newColorCode;
}

bool Board::verifyBonusPlace(int x, int y) {
    if (x <= 0 || x >= size - 1 || y <= 0 || y >= size - 1) { return false; }

    for (int row = -1; row <= 1; ++row) {
        for (int col = -1; col <= 1; ++col) {
            if (row == 0 && col == 0) { continue; }

            int rowx = x + row;
            int coly = y + col;

            if (rowx >= 0 && rowx < size && coly >= 0 && coly < size) {
                if (board[rowx][coly] == cell_state::BONUS) { return false; }
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
        do { x = dist(gen); y = dist(gen); } while (!verifyBonusPlace(x, y));
        board[x][y] = cell_state::BONUS;
        tileMapping[x][y] = std::make_shared<Tile>(bonus_state::ROBBERY);
    }

    for (int i = 0; i < number_stone; ++i) {
        int x, y; do { x = dist(gen); y = dist(gen);
        } while (!verifyBonusPlace(x, y));
        board[x][y] = cell_state::BONUS;
        tileMapping[x][y] = std::make_shared<Tile>(bonus_state::STONE);
    }

    for (int i = 0; i < number_tile_exchange; ++i) {
        int x, y;
        do { x = dist(gen); y = dist(gen); } while (!verifyBonusPlace(x, y));
        board[x][y] = cell_state::BONUS;
        tileMapping[x][y] = std::make_shared<Tile>(bonus_state::TILE_EXCHANGE);
    }
}

void Board::claimSurroundedBonuses() {
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            if (board[i][j] != cell_state::BONUS || !tileMapping[i][j] || tileMapping[i][j]->getOwnerId() != -1) { continue; }

            int surroundingOwnerId = -1;
            bool surroundedBySamePlayer = true;

            const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& dir : directions) {
                int neighborRow = i + dir[0];
                int neighborCol = j + dir[1];
                std::shared_ptr<Tile> neighborTile = tileMapping[neighborRow][neighborCol];

                if (!neighborTile || neighborTile->getOwnerId() == -1) { surroundedBySamePlayer = false; break; }

                if (surroundingOwnerId == -1) { surroundingOwnerId = neighborTile->getOwnerId(); }
                else if (neighborTile->getOwnerId() != surroundingOwnerId) { surroundedBySamePlayer = false; break; }
            }

            if (!surroundedBySamePlayer || surroundingOwnerId == -1) { continue; }

            tileMapping[i][j]->setOwnerId(surroundingOwnerId);
            auto player = players[surroundingOwnerId-1];

            switch (tileMapping[i][j]->getBonusState()) {
                case bonus_state::ROBBERY:
                    std::cout << player->getColor()
                              << "Player " << surroundingOwnerId << " (" << player->getName() << ")"
                              << " has claimed a Robbery Bonus!" << "\033[0m" << std::endl << std::endl;
                    player->addRobberyBonus(1);
                    break;
                case bonus_state::STONE:
                    std::cout << players[surroundingOwnerId - 1]->getColor()
                              << "Player " << surroundingOwnerId << " (" << player->getName() << ")"
                              << " has claimed a Stone Bonus!" << "\033[0m" << std::endl << std::endl;
                    player->addStoneBonus(1);
                    break;
                case bonus_state::TILE_EXCHANGE:
                    std::cout << players[surroundingOwnerId - 1]->getColor()
                              << "Player " << surroundingOwnerId << " (" << player->getName() << ")"
                              << " has claimed a Tile Exchange Bonus!" << "\033[0m" << std::endl << std::endl;
                    player->addTileExchangeCoupon(1);
                    break;
                default: break;
            }
        }
    }
}

bool Board::isTouchingPlayerTile(int boardRow, int boardCol, int ownerId, bool samePlayer) {
    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (const auto& dir : directions) {
        int neighborRow = boardRow + dir[0];
        int neighborCol = boardCol + dir[1];

        if (neighborRow >= 0 && neighborRow < size && neighborCol >= 0 && neighborCol < size) {
            std::shared_ptr<Tile> neighborTile = tileMapping[neighborRow][neighborCol];
            if (neighborTile && neighborTile->getOwnerId() != -1) {
                if ((samePlayer && neighborTile->getOwnerId() == ownerId) ||
                    (!samePlayer && neighborTile->getOwnerId() != ownerId)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::canPlaceTile(std::shared_ptr<Tile> tile, int row, int col, bool firstRound) {
    const auto& tileGrid = tile->getGrid();
    int ownerId = tile->getOwnerId();
    bool touchesSamePlayerTile = false;

    for (int i = 0; i < tileGrid.size(); ++i) {
        for (int j = 0; j < tileGrid[i].size(); ++j) {
            if (!tileGrid[i][j]) { continue; }

            int boardRow = row + i;
            int boardCol = col + j;

            if (boardRow < 0 || boardRow >= size || boardCol < 0 || boardCol >= size) { return false; }

            const auto& cellState = board[boardRow][boardCol];
            if (cellState != cell_state::EMPTY && cellState != cell_state::BONUS) { return false; }

            if (isTouchingPlayerTile(boardRow, boardCol, ownerId, false)) { return false; }
            if (!firstRound && isTouchingPlayerTile(boardRow, boardCol, ownerId, true)) { touchesSamePlayerTile = true; }
        }
    }

    return firstRound || touchesSamePlayerTile;
}

void Board::placeTile(std::shared_ptr<Tile> tile, int row, int col, cell_state cell_type) {
    int ownerId = tile->getOwnerId();
    cell_state cell = cell_type != EMPTY ? cell_type : static_cast<cell_state>(ownerId);
    for (int i = 0; i < tile->getGrid().size(); i++) {
        for (int j = 0; j < tile->getGrid()[0].size(); j++) {
            if (tile->getGrid()[i][j]) {
                board[row + i][col + j] = cell;
                tileMapping[row + i][col + j] = tile;
            }
        }
    }
}

void Board::removeTile(std::shared_ptr<Tile> tileToRemove) {
    if (!tileToRemove) return;

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            std::shared_ptr<Tile> currentTile = tileMapping[row][col];
            if (currentTile != tileToRemove) { continue; }

            tileMapping[row][col] = nullptr;
            board[row][col] = cell_state::EMPTY;
        }
    }
}

std::shared_ptr<Tile> Board::getTileAt(int row, int col) {
    return tileMapping[row][col];
}

cell_state Board::getCellAt(int row, int col) {
    return board[row][col];
}

bool Board::isStoneOnBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == cell_state::STONE_CELL) { return true; }
        }
    }
    return false;
}

std::shared_ptr<Player> Board::determineWinner() {
    int numPlayers = players.size();
    std::vector<int> maxSquareSize(numPlayers, 0);
    std::vector<int> total1x1Tiles(numPlayers, 0);

    std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            auto tile = tileMapping[i][j];
            if (!tile || tile->getOwnerId() <= 0) { continue; }

            int ownerId = tile->getOwnerId() - 1;
            dp[i][j] = 1;

            if (i > 0 && j > 0 && tileMapping[i-1][j] && tileMapping[i][j-1] && tileMapping[i-1][j-1]) {
                if (tileMapping[i-1][j]->getOwnerId() == tile->getOwnerId() &&
                    tileMapping[i][j-1]->getOwnerId() == tile->getOwnerId() &&
                    tileMapping[i-1][j-1]->getOwnerId() == tile->getOwnerId()) {
                    dp[i][j] = std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                }
            }

            maxSquareSize[ownerId] = std::max(maxSquareSize[ownerId], dp[i][j]);

            total1x1Tiles[ownerId]++;
        }
    }

    int maxTerritorySize = 0;
    int winnerPlayerId = -1;
    int max1x1Count = 0;

    for (int i = 0; i < numPlayers; ++i) {
        if (maxSquareSize[i] > maxTerritorySize) {
            maxTerritorySize = maxSquareSize[i];
            winnerPlayerId = i;
            max1x1Count = total1x1Tiles[i];
        } else if (maxSquareSize[i] == maxTerritorySize) {
            if (total1x1Tiles[i] > max1x1Count) {
                winnerPlayerId = i;
                max1x1Count = total1x1Tiles[i];
            }
        }
    }

    std::shared_ptr<Player> winner = players[winnerPlayerId];

    return winner;
}
