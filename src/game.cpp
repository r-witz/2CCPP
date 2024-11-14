#include "../include/game.hpp"

#include <iostream>
#include <memory>

Game::Game() {
    menu = Menu();
    tile_manager = TileManager();
    board = Board();
}

void Game::start() {
    if (!displayMainMenu()) {
        return;
    }

    initializePlayers();
    setupBoardAndTiles();
    playRounds(9);
    endGame();
}

bool Game::displayMainMenu() {
    menu.displayTitle();
    main_menu_options main_menu_option = menu.mainMenu();
    return main_menu_option == main_menu_options::PLAY;
}

void Game::initializePlayers() {
    player_number = menu.askPlayerNumber();
    for (int i = 1; i <= player_number; ++i) {
        player_color_options player_color = menu.playerColor(i);
        std::string player_name = menu.askPlayerName(i);
        auto player = std::make_shared<Player>(i, player_name, player_color);
        players.push_back(player);
    }
}

void Game::setupBoardAndTiles() {
    tile_manager.randomizeTileQueue(player_number);
    board = Board(player_number, players);
    board.placeBonus(player_number);

    for (auto& player : players) {
        std::shared_ptr<Tile> startingTile = std::make_shared<Tile>();
        startingTile->setOwnerId(player->getId());
        displayPlayerTurn(player, 0);
        playerPlaceTile(startingTile, player->getId(), true);
    }
}

void Game::playRounds(int totalRounds) {
    for (int round = 1; round <= totalRounds; ++round) {
        for (auto& player : players) {
            playTurn(player, round);
        }
    }
}

void Game::playTurn(std::shared_ptr<Player> player, int round) {
    displayPlayerTurn(player, round);
    std::cout << "Current Tile:" << std::endl;
    tile_manager.displayTiles(1, 0, -1, "");
    std::cout << "Next Tiles:" << std::endl;
    tile_manager.displayTiles(5, 1, -1, "");
    board.displayBoard();

    std::shared_ptr<Tile> selectedTile = selectTile(player);
    selectedTile->setOwnerId(player->getId());
    placeTile(selectedTile, player);
    board.claimSurroundedBonuses();
    useBonuses(player);
}

void Game::displayPlayerTurn(const std::shared_ptr<Player> player, int round) const {
    std::cout << player->getColor() << "Player " << player->getId() << " (" << player->getName() << ")" 
              << " - Round " << round << ":" << "\033[0m" << std::endl;
}

std::shared_ptr<Tile> Game::selectTile(const std::shared_ptr<Player> player) {
    std::shared_ptr<Tile> selectedTile;
    tile_selection_options tile_selection;
    bool isStoneToClear = board.isStoneOnBoard();

    do {
        tile_selection = menu.tileSelection(player->getTileExchangeCoupon(), isStoneToClear);
        switch (tile_selection) {
            case tile_selection_options::TAKE:
                selectedTile = tile_manager.getNextTile();
                break;
            case tile_selection_options::EXCHANGE:
                player->addTileExchangeCoupon(-1);
                selectedTile = tile_manager.chooseTile(player->getColor());
                break;
            case tile_selection_options::REMOVE_STONE:
                player->addTileExchangeCoupon(-1);
                playerRemoveStone(player->getId()-1);
                std::cout << "Current Tile:" << std::endl;
                tile_manager.displayTiles(1, 0, -1, "");
                std::cout << "Next Tiles:" << std::endl;
                tile_manager.displayTiles(5, 1, -1, "");
                board.displayBoard();
                break;
        }
    } while (tile_selection == tile_selection_options::REMOVE_STONE);

    return selectedTile;
}

void Game::placeTile(std::shared_ptr<Tile> &selectedTile, const std::shared_ptr<Player> player) {
    tile_action_options action;

    do {
        std::cout << "Tile to place:" << std::endl;
        selectedTile->display();
        action = menu.tileAction();

        switch (action) {
            case tile_action_options::FLIP:
                selectedTile->flip();
                menu.clearLines(10+selectedTile->getGrid().size());
                break;
            case tile_action_options::ROTATE:
                selectedTile->rotate();
                menu.clearLines(10+selectedTile->getGrid()[0].size());
                break;
            case tile_action_options::PLACE:
                if (!canPlaceTileAnywhere(selectedTile)) {
                    std::cout << "No valid placement available for this tile. Skipping placement." << std::endl << std::endl;
                    return;
                }
                playerPlaceTile(selectedTile, player->getId(), false);
                break;
        }
    } while (action != tile_action_options::PLACE);
}

bool Game::canPlaceTileAnywhere(std::shared_ptr<Tile> &tile) {
    int boardSize = board.getSize();
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board.canPlaceTile(tile, row, col, false)) { return true; }
        }
    }
    return false;
}

void Game::playerPlaceTile(std::shared_ptr<Tile> tile, int playerIndex, bool firstRound, bool bonusTilePlacement) {
    InputHandler inputHandler;
    int row = 0, col = 0;
    bool canPlace = board.canPlaceTile(tile, row, col, firstRound, bonusTilePlacement);

    inputs key;
    while(true) {
        board.displayBoard(display_mode::PLACING, row, col, playerIndex, tile, canPlace);

        key = inputHandler.getKeyPress();
        switch (key) {
            case UP: if (row > 0) --row; break;
            case DOWN: if (row + tile->getGrid().size() < board.getSize()) ++row; break;
            case LEFT: if (col > 0) --col; break;
            case RIGHT: if (col + tile->getGrid()[0].size() < board.getSize()) ++col; break;
            case ENTER: if (canPlace) { board.placeTile(tile, row, col); return; } else { menu.clearLines(board.getSize()+3); } break;
            default: break;
        }

        if (key != ENTER) { menu.clearLines(board.getSize() + 3); }
        canPlace = board.canPlaceTile(tile, row, col, firstRound, bonusTilePlacement);
    };
}

std::shared_ptr<Tile> Game::playerRemoveEnemyTile(int playerIndex) {
    InputHandler inputHandler;
    int row = 0, col = 0;
    std::shared_ptr<Tile> selectedTile = nullptr;

    inputs key;
    while (true) {
        board.displayBoard(display_mode::SELECTION, row, col, playerIndex);

        key = inputHandler.getKeyPress();
        switch (key) {
            case UP: if (row > 0) --row; break;
            case DOWN: if (row < board.getSize() - 1) ++row; break;
            case LEFT: if (col > 0) --col; break;
            case RIGHT: if (col < board.getSize() - 1) ++col; break;
            case ENTER: 
                selectedTile = board.getTileAt(row, col);
                if (selectedTile && selectedTile->getOwnerId() > 0 && selectedTile->getOwnerId() != playerIndex + 1) {
                    board.removeTile(selectedTile);
                    return selectedTile;
                } else { menu.clearLines(board.getSize() + 3); }
                break;
            default: break;
        }

        if (key != ENTER) { menu.clearLines(board.getSize() + 3); }
    }
}

void Game::playerRemoveStone(int playerIndex) {
    InputHandler inputHandler;
    int row = 0, col = 0;
    std::shared_ptr<Tile> selectedTile = nullptr;
    std::shared_ptr<Tile> previewTile = std::make_shared<Tile>();

    inputs key;
    while (true) {
        board.displayBoard(display_mode::PLACING, row, col, playerIndex, previewTile, false);

        key = inputHandler.getKeyPress();
        switch (key) {
            case UP: if (row > 0) --row; break;
            case DOWN: if (row < board.getSize() - 1) ++row; break;
            case LEFT: if (col > 0) --col; break;
            case RIGHT: if (col < board.getSize() - 1) ++col; break;
            case ENTER:
                selectedTile = board.getTileAt(row, col);
                if (selectedTile && board.getCellAt(row, col) == STONE_CELL) {
                    board.removeTile(selectedTile);
                    return;
                }
                break;
            default: break;
        }
        menu.clearLines(board.getSize() + 3);
    }
}

void Game::playerPlaceStone(int playerIndex) {
    InputHandler inputHandler;
    int row = 0, col = 0;
    bool canPlace = false;
    std::shared_ptr<Tile> previewTile = std::make_shared<Tile>();

    inputs key;
    while (true) {
        board.displayBoard(display_mode::PLACING, row, col, playerIndex, previewTile, false);

        key = inputHandler.getKeyPress();
        switch (key) {
            case UP: if (row > 0) --row; break;
            case DOWN: if (row < board.getSize() - 1) ++row; break;
            case LEFT: if (col > 0) --col; break;
            case RIGHT: if (col < board.getSize() - 1) ++col; break;
            case ENTER:
                if (!board.getTileAt(row, col)) {
                    std::shared_ptr<Tile> stoneTile = std::make_shared<Tile>();
                    board.placeTile(stoneTile, row, col, STONE_CELL);
                    return;
                }
                break;
            default: break;
        }
        menu.clearLines(board.getSize() + 3);
    }
}

void Game::useBonuses(std::shared_ptr<Player> player) {
    int playerIndex = player->getId() - 1;

    while (player->getRobberyBonus() > 0) {
        std::cout << "You have a robbery bonus! Select an enemy tile to steal." << std::endl << std::endl;
        std::shared_ptr<Tile> stolenTile = playerRemoveEnemyTile(playerIndex);
        std::cout << "Tile stolen! You can now modify and place it." << std::endl << std::endl;
        player->addRobberyBonus(-1);

        stolenTile->setOwnerId(player->getId());
        placeTile(stolenTile, player);
    }

    while (player->getStoneBonus() > 0) {
        std::cout << "You have a stone bonus! Place it on an empty cell." << std::endl << std::endl;
        playerPlaceStone(playerIndex);
        player->addStoneBonus(-1);
    }

}

void Game::placeBonusTile() {
    bonus_tiles_options action;
    for (int i = 0; i < players.size(); ++i) {
        while (players[i]->getTileExchangeCoupon() > 0) {
            std::cout << "Player " << players[i]->getId() << " has a tile exchange coupon." << std::endl << std::endl;
            action = menu.bonusTiles(players[i]->getTileExchangeCoupon());
            std::shared_ptr<Tile> tile;
            switch (action) {
                case bonus_tiles_options::YES:
                    tile = std::make_shared<Tile>();
                    tile->setOwnerId(players[i]->getId());
                    playerPlaceTile(tile, players[i]->getId(), false, true);
                    break;
                case bonus_tiles_options::NO:
                    break;
            }
            players[i]->addTileExchangeCoupon(-1);
        }
    }
}

void Game::endGame() {
    placeBonusTile();
    auto winner = board.determineWinner();
    menu.displayWinner(winner->getId());
}
