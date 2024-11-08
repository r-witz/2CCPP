#include "../include/game.hpp"

Game::Game() {
    menu = Menu();
    tile_manager = TileManager();
    board = Board();
}

void Game::playerPlaceTile(std::shared_ptr<Tile> tile, int playerIndex, bool firstRound) {
    InputHandler inputHandler;
    int row = 0, col = 0;
    bool canPlace = board.canPlaceTile(tile, row, col, firstRound);

    while (true) {
        board.displayBoard(tile, row, col, playerIndex, canPlace);

        inputs key = inputHandler.getKeyPress();
        switch (key) {
            case UP:
                if (row > 0) --row;
                break;
            case DOWN:
                if (row + tile->getGrid().size() < board.getSize()) ++row;
                break;
            case LEFT:
                if (col > 0) --col;
                break;
            case RIGHT:
                if (col + tile->getGrid()[0].size() < board.getSize()) ++col;
                break;
            case ENTER:
                if (canPlace) {
                    board.placeTile(tile, row, col);
                    return;
                }
                break;
            default:
                break;
        }

        canPlace = board.canPlaceTile(tile, row, col, firstRound);
    }
}

void Game::start() {
    menu.displayTitle();
    main_menu_options main_menu_option = menu.mainMenu();

    switch (main_menu_option) {
        case main_menu_options::PLAY: break;
        case main_menu_options::EXIT: return;
    }

    player_number = menu.askPlayerNumber();

    for (int i = 1; i <= player_number; i++) {
        player_color_options player_color = menu.playerColor(i);
        std::string player_name = menu.askPlayerName(i);
        players.push_back(Player(i, player_name, player_color));
    }

    tile_manager.randomizeTileQueue(player_number);
    board = Board(player_number, players);

    for (int i = 0; i < player_number; ++i) {
        std::shared_ptr<Tile> startingTile = std::make_shared<Tile>();
        startingTile->setOwnerId(players[i].getId());
        playerPlaceTile(startingTile, players[i].getId(), true);
    }

    for (int round = 2; round <= 9; ++round) {
        for (int i = 0; i < player_number; ++i) {
            std::shared_ptr<Tile> selectedTile = tile_manager.getNextTile();
            selectedTile->setOwnerId(players[i].getId());
            playerPlaceTile(selectedTile, players[i].getId(), false);
        }
    }
}
