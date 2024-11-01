#ifndef MENU_HPP
#define MENU_HPP

#include <string>

enum main_menu_options { PLAY, EXIT };
enum player_color_options { RED, BLUE, GREEN, YELLOW, PINK, BROWN, CYAN, ORANGE, VIOLET };

class Menu {
private:
    void displayMainMenu(main_menu_options selected_option);

public:
    Menu();

    void displayTitle();
    main_menu_options mainMenu();
    
    int askPlayerNumber();
    std::string askPlayerName(int player_number);
};

#endif
