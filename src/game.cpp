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
            for (int i = 0; i < player_number; i++) {
                std::string player_name = menu.askPlayerName(i + 1);
                std::cout << "Player " << i + 1 << " name: " << player_name << std::endl;
            }
            for (int i = 0; i < player_number; i++) {
                std::cout << "Player " << i + 1 << " choose your color:" << std::endl;
                std::string player_color = menu.askPlayerColor(i + 1, player_color_options::RED);
                std::cout << "Player " << i + 1 << " color: " << player_color << std::endl;
            }
        case main_menu_options::EXIT:
            return;
    }
};
