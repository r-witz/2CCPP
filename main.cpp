#include "include/input_handler.hpp"

#include <iostream>

int main() {
    InputHandler input_handler = InputHandler();

    inputs input;
    while (input != inputs::ENTER) {
        do {
            input = input_handler.getKeyPress();
        } while (input == inputs::NONE);

        switch (input) {
            case inputs::UP:
                std::cout << "UP" << std::endl;
                break;
            case inputs::DOWN:
                std::cout << "DOWN" << std::endl;
                break;
            case inputs::LEFT:
                std::cout << "LEFT" << std::endl;
                break;
            case inputs::RIGHT:
                std::cout << "RIGHT" << std::endl;
                break;
            case inputs::ENTER:
                std::cout << "ENTER" << std::endl;
                break;
            default:
                std::cout << "NONE" << std::endl;
        }
    }

    return 0;
}
