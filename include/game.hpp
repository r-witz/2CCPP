#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"
#include "tile_manager.hpp"
#include "board.hpp"
#include "player.hpp"
#include <memory>
#include <vector>

class Game {
private:
    Menu menu;
    TileManager tile_manager;
    Board board;
    int player_number;
    std::vector<std::shared_ptr<Player>> players;

    bool displayMainMenu();
    void initializePlayers();
    void setupBoardAndTiles();
    void playRounds(int totalRounds);
    void playTurn(std::shared_ptr<Player> player, int round);
    std::shared_ptr<Tile> selectTile(const std::shared_ptr<Player> player);
    void placeTile(std::shared_ptr<Tile>& selectedTile, const std::shared_ptr<Player> player);
    bool canPlaceTileAnywhere(std::shared_ptr<Tile> &tile);
    void displayPlayerTurn(const std::shared_ptr<Player> player, int round) const;
    void playerPlaceTile(std::shared_ptr<Tile> tile, int playerIndex, bool firstRound);
    std::shared_ptr<Tile> playerRemoveEnemyTile(int playerIndex);
    void playerRemoveStone(int playerIndex);
    void playerPlaceStone(int playerIndex);
    void useBonuses(std::shared_ptr<Player> player);
    void placeBonusTile();
    void endGame();

public:
    Game();

    void start();
};

#endif
