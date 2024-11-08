#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

class Tile {
private:
    std::vector<std::vector<bool>> grid;
    int owner_id;
    int cluster_id;

public:
    Tile();
    Tile(const std::vector<std::vector<bool>> &grid, int owner_id = -1, int cluster_id = -1);

    std::vector<std::vector<bool>> getGrid();

    int getOwnerId();
    void setOwnerId(int id);

    int getClusterId();
    void setClusterId(int id);

    void flip();
    void rotate();
    void display();
};

#endif
