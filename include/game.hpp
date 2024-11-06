#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"
#include "tile_manager.hpp"
#include "board.hpp"
#include "player.hpp"

class Game {
private:
    Menu menu;
    TileManager tile_manager;
    Board board;
    int player_number;
    std::vector<Player> players;

public:
    Game();

    void start();
};

#endif
