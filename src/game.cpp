#include "../include/game.hpp"

Game::Game() {
    menu = Menu();
    tile_manager = TileManager();
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
    }

    tile_selection_options tile_selection_option = menu.tileSelection(1);
    Tile selected_tile = tile_manager.getNextTile();
    switch (tile_selection_option) {
        case tile_selection_options::TAKE:
            break;
        case tile_selection_options::EXCHANGE:
            tile_manager.chooseTile();
            break;
    }

    selected_tile.display();

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
            break;
    }

    menu.displayWinner(1);
};
