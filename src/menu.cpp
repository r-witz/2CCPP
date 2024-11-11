#include "../include/menu.hpp"
#include "../include/input_handler.hpp"

#include <iostream>
#include <vector>

Menu::Menu() {
    input_handler = InputHandler();
}

void Menu::clearLines(int numLines) const {
    for (int i = 0; i < numLines; ++i) {
        std::cout << "\033[F" << "\033[K";
    }
}

void Menu::displayTitle() {
    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << "|   Laying Grass   |" << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}

void Menu::displayMainMenu(main_menu_options selected_option) {
    std::string playLine = "|       Play       |";
    std::string exitLine = "|       Exit       |";

    switch (selected_option) {
        case main_menu_options::PLAY:
            playLine = "|     ▶ Play       |";
            break;
        case main_menu_options::EXIT:
            exitLine = "|     ▶ Exit       |";
    }

    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << playLine << std::endl
              << exitLine << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}

main_menu_options Menu::mainMenu() {
    main_menu_options selected_option = main_menu_options::PLAY;
    inputs input;

    do {
        displayMainMenu(selected_option);
        input = input_handler.getKeyPress();
        if (input == inputs::UP || input == inputs::DOWN) {
            selected_option = selected_option == main_menu_options::PLAY ? main_menu_options::EXIT : main_menu_options::PLAY;
        }

        if (input != inputs::ENTER) { clearLines(7); };

    } while(input != inputs::ENTER);

    return selected_option;
}

void Menu::displayPlayerColor(int player_number, player_color_options selected_option, std::set<player_color_options> selected_colors) {
    std::string colorLines[9] = {
        "|       Red        |",
        "|       Blue       |",
        "|       Green      |",
        "|       Yellow     |",
        "|       Pink       |",
        "|       Brown      |",
        "|       Cyan       |",
        "|       Orange     |",
        "|       Violet     |"
    };

    for (int i = 0; i < 9; ++i) {
        player_color_options color = static_cast<player_color_options>(i);
        if (selected_colors.count(color) > 0) { colorLines[i] = ""; }
        else if (color == selected_option) {
            switch (color) {
                case player_color_options::RED: colorLines[i] = "|     ▶ Red        |"; break;
                case player_color_options::BLUE: colorLines[i] = "|     ▶ Blue       |"; break;
                case player_color_options::GREEN: colorLines[i] = "|     ▶ Green      |"; break;
                case player_color_options::YELLOW: colorLines[i] = "|     ▶ Yellow     |"; break;
                case player_color_options::PINK: colorLines[i] = "|     ▶ Pink       |"; break;
                case player_color_options::BROWN: colorLines[i] = "|     ▶ Brown      |"; break;
                case player_color_options::CYAN: colorLines[i] = "|     ▶ Cyan       |"; break;
                case player_color_options::ORANGE: colorLines[i] = "|     ▶ Orange     |"; break;
                case player_color_options::VIOLET: colorLines[i] = "|     ▶ Violet     |"; break;
            }
        }
    }

    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << "|     Player " << player_number << "     |" << std::endl
              << "|  Choose a color  |" << std::endl
              << "|                  |" << std::endl;

    for (const auto& line : colorLines) {
        if (!line.empty()) {
            std::cout << line << std::endl;
        }
    }

    std::cout << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}

player_color_options Menu::playerColor(int player_number) {
    std::vector<player_color_options> unselected_colors;
    for (int i = 0; i < 9; ++i) {
        player_color_options color = static_cast<player_color_options>(i);
        if (selected_colors.count(color) == 0) { unselected_colors.push_back(color); }
    }

    int option_count = unselected_colors.size();
    int selected_index = 0;
    player_color_options selected_option = unselected_colors[selected_index];
    inputs input;

    do {
        displayPlayerColor(player_number, selected_option, selected_colors);
        input = input_handler.getKeyPress();

        if (input == inputs::UP) { selected_index = (selected_index - 1 + option_count) % option_count; }
        else if (input == inputs::DOWN) { selected_index = (selected_index + 1) % option_count; }
        selected_option = unselected_colors[selected_index];

        if (input != inputs::ENTER) { clearLines(8+option_count); };
    } while (input != inputs::ENTER);

    selected_colors.insert(selected_option);
    return selected_option;
}

void Menu::displayTileSelection(int exchange_coupon, tile_selection_options selected_option) {
    std::string takeLine = "|    Take          |";
    std::string exchangeLine = "|    Exchange (" + std::to_string(exchange_coupon) + ")  |";

    switch (selected_option) {
        case tile_selection_options::TAKE:
            takeLine = "|  ▶ Take          |";
            break;
        case tile_selection_options::EXCHANGE:
            exchangeLine = "|  ▶ Exchange (" + std::to_string(exchange_coupon) + ")  |";
    }

    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << takeLine << std::endl
              << exchangeLine << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}


tile_selection_options Menu::tileSelection(int exchange_coupon) {
    tile_selection_options selected_option = tile_selection_options::TAKE;
    inputs input;

    do {
        displayTileSelection(exchange_coupon, selected_option);
        input = input_handler.getKeyPress();
        if (input == inputs::UP || input == inputs::DOWN) {
            selected_option = selected_option == tile_selection_options::TAKE ? tile_selection_options::EXCHANGE : tile_selection_options::TAKE;
        }

        if (input != inputs::ENTER) { clearLines(7); }
        else if (input == inputs::ENTER && selected_option == tile_selection_options::EXCHANGE && exchange_coupon == 0) { clearLines(7); continue;}
    } while(input != inputs::ENTER || (selected_option == tile_selection_options::EXCHANGE && exchange_coupon == 0));

    return selected_option;
}


void Menu::displayTileAction(tile_action_options selected_option) {
    std::string flipLine = "|      Flip        |";
    std::string rotateLine = "|      Rotate      |";
    std::string placeLine = "|      Place       |";

    switch (selected_option) {
        case tile_action_options::FLIP:
            flipLine = "|    ▶ Flip        |";
            break;
        case tile_action_options::ROTATE:
            rotateLine = "|    ▶ Rotate      |";
            break;
        case tile_action_options::PLACE:
            placeLine = "|    ▶ Place       |";
    }

    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << flipLine << std::endl
              << rotateLine << std::endl
              << placeLine << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;

}


tile_action_options Menu::tileAction() {
    tile_action_options selected_option = tile_action_options::FLIP;
    inputs input;

    do {
        displayTileAction(selected_option);
        input = input_handler.getKeyPress();

        if (input == inputs::UP) { selected_option = tile_action_options((static_cast<int>(selected_option) - 1 + 3) % 3); }
        else if (input == inputs::DOWN) { selected_option = tile_action_options((static_cast<int>(selected_option) + 1) % 3); }

        if (input != inputs::ENTER) { clearLines(8); };
    } while (input != inputs::ENTER);

    return selected_option;

};

void Menu::displayWinner(int player_number) {
    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << "|     Player " << player_number << "     |" << std::endl
              << "|       Wins       |" << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}

int Menu::askPlayerNumber() {
    std::string buffer;
    int player_number;

    do {
        std::cout << "Enter a number of player (2-9): ";
        std::getline(std::cin, buffer);

        try {
            player_number = std::stoi(buffer);

            if (2 <= player_number && player_number <= 9) { return player_number; }
            else { std::cout << "Please enter a number between 2 and 9.\n"; }
        }
        catch (const std::invalid_argument&) { std::cout << "Invalid input. Please enter a number between 2 and 9.\n"; }
        catch (const std::out_of_range&) { std::cout << "The number is out of range. Please enter a number between 2 and 9.\n"; }

    } while (true);
}

std::string Menu::askPlayerName(int player_number) {
    std::string player_name;
    std::cout << "Player " << player_number << " , enter your name: ";
    std::getline(std::cin, player_name);
    std::cout << std::endl;
    return player_name;
}

std::string Menu::getColorName(player_color_options selected_option) {
    switch (selected_option) {
        case player_color_options::RED: return "Red";
        case player_color_options::BLUE: return "Blue";
        case player_color_options::GREEN: return "Green";
        case player_color_options::YELLOW: return "Yellow";
        case player_color_options::PINK: return "Pink";
        case player_color_options::BROWN: return "Brown";
        case player_color_options::CYAN: return "Cyan";
        case player_color_options::ORANGE: return "Orange";
        case player_color_options::VIOLET: return "Violet";
        default: return "";
    }
}
