#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"
#include "tiles.hpp"

class Game {
private:
    Menu menu;
    Tiles tiles;
    int player_number;

public:
    Game();

    void start();
};

#endif
