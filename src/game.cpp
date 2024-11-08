#include "../include/game.hpp"

Game::Game() {
    menu = Menu();
    tile_manager = TileManager();
    board = Board();
}

void Game::playerPlaceTile(Tile* tile, int playerIndex, bool firstRound) {
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
    tile_manager.randomizeTileQueue(player_number);

    for (int i = 1; i <= player_number; i++) {
        player_color_options player_color = menu.playerColor(i);
        std::string player_name = menu.askPlayerName(i);
        players.push_back(Player(i, player_name, player_color));
    }

    board = Board(player_number, players);

    tile_selection_options tile_selection_option = menu.tileSelection(1);
    Tile selected_tile = tile_manager.getNextTile();
    switch (tile_selection_option) {
        case tile_selection_options::TAKE:
            break;
        case tile_selection_options::EXCHANGE:
            tile_manager.chooseTile(players[0].getColor());
            break;
    }

    selected_tile.display();
    selected_tile.setOwnerId(players[0].getId());

    tile_action_options tile_action_option = menu.tileAction();
    switch (tile_action_option) {
        case tile_action_options::FLIP:
            selected_tile.flip();
            selected_tile.display();
            break;
        case tile_action_options::ROTATE:
            selected_tile.rotate();
            selected_tile.display();
            break;
        case tile_action_options::PLACE:
            board.placeBonus(player_number);
            playerPlaceTile(&selected_tile, players[0].getId(), true);
            break;
    }

    board.displayBoard();
    menu.displayWinner(1);
};
