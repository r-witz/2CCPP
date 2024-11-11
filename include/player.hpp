#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "menu.hpp"

class Player {
private:
    int id;
    std::string name;
    std::string color;
    int tile_exchange_coupon;

public:
    Player(int id, std::string name, enum player_color_options color);

    int getId() const;
    std::string getName() const;
    std::string getColor() const;
    int getTileExchangeCoupon() const;
    void addTileExchangeCoupon(int number);
};

#endif
