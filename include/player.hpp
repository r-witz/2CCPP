#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "menu.hpp"

class Player {
private:
    int number;
    std::string name;
    std::string color;

public:
    Player(int number, std::string name, enum player_color_options color);

    int getNumber();
    std::string getName();
    std::string getColor();
};

#endif
