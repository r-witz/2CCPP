#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

enum bonus_state {NOB, TILE_EXCHANGE, STONE, ROBBERY};

class Tile {
private:
    std::vector<std::vector<bool>> grid;
    int owner_id;
    bonus_state bonus_type;

public:
    Tile();
    Tile(bonus_state bonus_type);
    Tile(const std::vector<std::vector<bool>> &grid, int owner_id = -1);

    std::vector<std::vector<bool>> getGrid();

    int getOwnerId();
    void setOwnerId(int id);
    bonus_state getBonusState();

    void flip();
    void rotate();
    void display();
};

#endif
