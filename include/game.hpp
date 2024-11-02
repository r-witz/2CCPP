#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"
#include "tile_manager.hpp"

class Game {
private:
    Menu menu;
    TileManager tile_manager;
    int player_number;

public:
    Game();

    void start();
};

#endif
