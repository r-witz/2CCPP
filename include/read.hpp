#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <string>
#include <vector>

class Read {
    public:
    static std::vector<std::string> readText(const std::string &filePath);
    static std::vector<std::string> transformText(const std::vector<std::string> &texts);
};

#endif