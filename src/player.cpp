#include "../include/player.hpp"

Player::Player(int id, std::string name, enum player_color_options color) {
    this->id = id;
    this->name = name;

    switch (color) {
        case player_color_options::RED: this->color = "\033[38;2;255;0;0m"; break;
        case player_color_options::BLUE: this->color = "\033[38;2;0;0;255m"; break;
        case player_color_options::GREEN: this->color = "\033[38;2;0;255;0m"; break;
        case player_color_options::YELLOW: this->color = "\033[38;2;255;255;0m"; break;
        case player_color_options::PINK: this->color = "\033[38;2;255;0;255m"; break;
        case player_color_options::BROWN: this->color = "\033[38;2;128;0;0m"; break;
        case player_color_options::CYAN: this->color = "\033[38;2;0;255;255m"; break;
        case player_color_options::ORANGE: this->color = "\033[38;2;255;102;0m"; break;
        case player_color_options::VIOLET: this->color = "\033[38;2;204;153;255m"; break;
    }
}

int Player::getId() {
    return id;
}

std::string Player::getName() {
    return name;
}

std::string Player::getColor() {
    return color;
}
