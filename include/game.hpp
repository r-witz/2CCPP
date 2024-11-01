#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"

class Game {
private:
    Menu menu;
    int player_number;

public:
    Game();

    void start();
};

#endif
