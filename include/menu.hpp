#ifndef MENU_HPP
#define MENU_HPP

#include "input_handler.hpp"

#include <string>
#include <set>

enum main_menu_options { PLAY, EXIT };
enum player_color_options { RED, BLUE, GREEN, YELLOW, PINK, BROWN, CYAN, ORANGE, VIOLET };

class Menu {
private:
    InputHandler input_handler;

    void displayMainMenu(main_menu_options selected_option);
    void displayPlayerColor(int player_number, player_color_options selected_option, std::set<player_color_options> selected_colors);
    std::set<player_color_options> selected_colors;

public:
    Menu();

    void displayTitle();
    main_menu_options mainMenu();
    player_color_options playerColor(int player_number);

    int askPlayerNumber();
    std::string askPlayerName(int player_number);

    std::string getColorName(player_color_options color);
};

#endif
