#ifndef MENU_HPP
#define MENU_HPP

#include "input_handler.hpp"

#include <string>
#include <set>

enum main_menu_options { PLAY, EXIT };
enum player_color_options { RED, BLUE, GREEN, YELLOW, PINK, BROWN, CYAN, ORANGE, VIOLET };
enum tile_selection_options { TAKE, EXCHANGE, REMOVE_STONE };
enum tile_action_options { FLIP, ROTATE, PLACE };
enum bonus_tiles_options { YES, NO };

class Menu {
private:
    InputHandler input_handler;
    std::set<player_color_options> selected_colors;

    void displayMainMenu(main_menu_options selected_option);
    void displayPlayerColor(int player_number, player_color_options selected_option, std::set<player_color_options> selected_colors);
    void displayTileSelection(int exchange_coupon, tile_selection_options selected_option);
    void displayTileAction(tile_action_options selected_option);
    void displayBonusTilesMenu(int exchange_coupon, bonus_tiles_options selected_option);

public:
    Menu();

    void clearLines(int numLines) const;
    void displayTitle();
    main_menu_options mainMenu();
    player_color_options playerColor(int player_number);
    tile_selection_options tileSelection(int exchange_coupon, bool isStoneToClear);
    tile_action_options tileAction();
    bonus_tiles_options bonusTiles(int exchange_coupon);
    void displayWinner(int player_number);

    int askPlayerNumber();
    std::string askPlayerName(int player_number);

    std::string getColorName(player_color_options color);
};

#endif
