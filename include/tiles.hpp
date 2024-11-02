#ifndef TILES_HPP
#define TILES_HPP

#include <iostream>
#include <string>
#include <vector>

class Tiles {
private:

public:
    Tiles();

    static std::vector<std::string> readText(const std::string &filePath);
    static std::vector<std::string> transformText(const std::vector<std::string> &texts);
    static std::vector<std::string> displayTiles(const std::vector<std::string> &texts, int display_number);
    static std::vector<std::string> rotateTiles(const std::vector<std::string> &texts, int rotation_number);
    static std::vector<std::string> flipTiles(const std::vector<std::string> &texts);
};

#endif