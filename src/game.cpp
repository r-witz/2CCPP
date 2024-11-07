#include "../include/game.hpp"

#include <iostream>

Game::Game() {
    menu = Menu();
    tile_manager = TileManager();
    board = Board();
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
    board = Board(player_number);

    for (int i = 1; i <= player_number; i++) {
        player_color_options player_color = menu.playerColor(i);
        std::string player_name = menu.askPlayerName(i);
        players.push_back(Player(i, player_name, player_color));
    }

    for (int i = 0; i < player_number; i++) {
        std::cout << "Number: " << players[i].getNumber() << std::endl
                  << "Name: " << players[i].getName() << std::endl
                  << "Color: " << players[i].getColor() << "TEST" << "\033[0m" << std::endl;
    }

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
            break;
    }

    menu.displayWinner(1);
};
