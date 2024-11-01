#include "../include/game.hpp"

#include <iostream>

Game::Game() {
    menu = Menu();
    player_number = 0;
}

void Game::start() {
    menu.displayTitle();
    main_menu_options selected_option = menu.mainMenu();

    switch (selected_option) {
        case main_menu_options::PLAY:
            player_number = menu.askPlayerNumber();
            std::cout << "Number of Players: " << player_number << std::endl;
            break;
        case main_menu_options::EXIT:
            return;
    }
};
