#include "../include/input_handler.hpp"
#include "../include/getch.hpp"

InputHandler::InputHandler() {}

inputs InputHandler::getKeyPress() {
    char key = getch();

    if (key == '\033') {
        char second = getch();
        if (second == '[') {
            char third = getch();
            switch (third) {
                case 'A': return UP;    // Arrow Up
                case 'B': return DOWN;  // Arrow Down
                case 'C': return RIGHT; // Arrow Right
                case 'D': return LEFT;  // Arrow Left
            }
        }
    }

    switch (key) {
        case 'z':
        case 'Z':
            return UP;
        case 's':
        case 'S':
            return DOWN;
        case 'd':
        case 'D':
            return RIGHT;
        case 'q':
        case 'Q':
            return LEFT;
        case '\r':
        case '\n':
            return ENTER;
        default:
            return NONE;
    }
}
