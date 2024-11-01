#include "../include/menu.hpp"
#include "../include/input_handler.hpp"

#include <iostream>

Menu::Menu() {}

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
    InputHandler input_handler = InputHandler();
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

            if (player_number >= 2 && player_number <= 9) { return player_number; }
            else { std::cout << "Please enter a number between 2 and 9.\n"; }
        }
        catch (const std::invalid_argument&) { std::cout << "Invalid input. Please enter a number between 2 and 9.\n"; }
        catch (const std::out_of_range&) { std::cout << "The number is out of range. Please enter a number between 2 and 9.\n"; }

    } while (true);
}

std::string Menu::askPlayerName(int player_number) {
    std::string player_name;
    std::cout << "Choose a name for Player " << player_number << ": ";
    std::getline(std::cin, player_name);
    return player_name;
}

