#include "../include/menu.hpp"
#include "../include/input_handler.hpp"

#include <iostream>

Menu::Menu() {
    input_handler = InputHandler();
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

    } while(input != inputs::ENTER);

    return selected_option;
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
    return player_name;
}

void Menu::displayPlayerColor(int player_number, player_color_options selected_option) {
    int colorNumber = player_number;
    std::string redLine = "|       Red        |";
    std::string blueLine = "|       Blue       |";
    std::string greenLine = "|       Green      |";
    std::string yellowLine = "|       Yellow     |";
    std::string pinkLine = "|       Pink       |";
    std::string brownLine = "|       Brown      |";
    std::string cyanLine = "|       Cyan       |";
    std::string orangeLine = "|       Orange     |";
    std::string violetLine = "|       Violet     |";

    switch (selected_option) {
        case player_color_options::RED:
            redLine = "|     ▶ Red        |";
            break;
        case player_color_options::BLUE:
            blueLine = "|     ▶ Blue       |";
            break;
        case player_color_options::GREEN:
            greenLine = "|     ▶ Green      |";
            break;
        case player_color_options::YELLOW:
            yellowLine = "|     ▶ Yellow     |";
            break;
        case player_color_options::PINK:
            pinkLine = "|     ▶ Pink       |";
            break;
        case player_color_options::BROWN:
            brownLine = "|     ▶ Brown      |";
            break;
        case player_color_options::CYAN:
            cyanLine = "|     ▶ Cyan       |";
            break;
        case player_color_options::ORANGE:
            orangeLine = "|     ▶ Orange     |";
            break;
        case player_color_options::VIOLET:
            violetLine = "|     ▶ Violet     |";
            break;
    }

    std::cout << "+------------------+" << std::endl
              << "|                  |" << std::endl
              << redLine << std::endl
              << blueLine << std::endl
              << greenLine << std::endl
              << yellowLine << std::endl
              << pinkLine << std::endl
              << brownLine << std::endl
              << cyanLine << std::endl
              << orangeLine << std::endl
              << violetLine << std::endl
              << "|                  |" << std::endl
              << "+------------------+" << std::endl
              << std::endl;
}

std::string Menu::getColorName(player_color_options selected_option) {
    switch (selected_option) {
        case player_color_options::RED:
            return "Red";
        case player_color_options::BLUE:
            return "Blue";
        case player_color_options::GREEN:
            return "Green";
        case player_color_options::YELLOW:
            return "Yellow";
        case player_color_options::PINK:
            return "Pink";
        case player_color_options::BROWN:
            return "Brown";
        case player_color_options::CYAN:
            return "Cyan";
        case player_color_options::ORANGE:
            return "Orange";
        case player_color_options::VIOLET:
            return "Violet";
        default:
            return "";
    }
}

std::string Menu::askPlayerColor(int player_number, player_color_options selected_option) {
    inputs input;

    do {
        displayPlayerColor(player_number, selected_option);
        input = input_handler.getKeyPress();

        do {
            if (input == inputs::UP) {
                selected_option = player_color_options((static_cast<int>(selected_option) - 1 + 9) % 9);
            } else if (input == inputs::DOWN) {
                selected_option = player_color_options((static_cast<int>(selected_option) + 1) % 9);
            }
        } while (taken_colors.find(selected_option) != taken_colors.end());

    } while (input != inputs::ENTER);

    taken_colors.insert(selected_option);
    return getColorName(selected_option);
}


