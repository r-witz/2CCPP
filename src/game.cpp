#include "../include/game.hpp"

#include <iostream>

Game::Game() {
    menu = Menu();
    tiles = Tiles();
    player_number = 0;
}

void Game::start() {
    menu.displayTitle();
    main_menu_options selected_option = menu.mainMenu();

    switch (selected_option) {
        case main_menu_options::PLAY:
            break;
        case main_menu_options::EXIT:
            return;
    }

    player_number = menu.askPlayerNumber();

    for (int i = 1; i <= player_number; i++) {
        player_color_options player_color = menu.playerColor(i);
        std::string player_name = menu.askPlayerName(i);
    }

    tiles.readText("data/tiles.txt");
    tiles.transformText(tiles.readText("data/tiles.txt"));
    
    std::cout << "Tile to place: " << std::endl << std::endl;
    tiles.displayTiles(tiles.transformText(tiles.readText("data/tiles.txt")), 0);
    menu.tileSelection(2);
    menu.tileAction();
    menu.displayWinner(1);
};
