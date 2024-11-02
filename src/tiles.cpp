#include "../include/tiles.hpp"
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> Read::readText(const std::string &filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> texts; 
    std::string text;
    
    if (!file) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return texts;
    } else {
        std::string line;
        int emptyLineCount = 0;

        while (std::getline(file, line)) {
            if (line.empty()) {
                emptyLineCount++;
                
                if (emptyLineCount == 1) {
                    if (!text.empty()) {
                        texts.push_back(text);
                        text.clear();
                    }
                }
            } else {
                emptyLineCount = 0;
                text += line + "\n";
            }
        }
        
        if (!text.empty()) {
            texts.push_back(text);
        }

        file.close();
        return texts;
    }
}

std::vector<std::string> Read::transformText(const std::vector<std::string> &texts) {
    std::vector<std::string> transformedTexts;

    for (const std::string &text : texts) {
        std::string transformedText;

        for (char character : text) {
            if (character == '1') {
                transformedText += "\xE2\x96\x88\xE2\x96\x88";
            } else if (character == '0') {
                transformedText += "  ";
            } else {
                transformedText += character;
            }
        }

        transformedTexts.push_back(transformedText);
    }

    return transformedTexts;
}

std::vector<std::string> Read::rotateTiles(const std::vector<std::string> &texts, int rotation_number) {
    std::vector<std::string> rotatedTiles;

    for (const std::string &text : texts) {
        std::vector<std::string> lines;
        std::string line;

        for (char character : text) {
            if (character == '\n') {
                lines.push_back(line);
                line.clear();
            } else {
                line += character;
            }
        }

        if (!line.empty()) {
            lines.push_back(line);
        }


        for (int z = 0; z < rotation_number; ++z) {
            int Rows = lines.size();
            int Cols = lines.empty() ? 0 : lines[0].size();
            std::vector<std::string> rotatedLines(Cols, std::string(Rows, ' '));

            for (int j = 0; j < Cols; ++j) {
                for (int i = Rows - 1; i >= 0; --i) {
                    rotatedLines[j][Rows - 1 - i] = lines[i][j];
                }
            }
            lines = rotatedLines;
        }

        std::string rotatedText;
        for (const std::string &rotatedLine : lines) {
            rotatedText += rotatedLine + '\n';
        }

        std::string transformedText;
        for (char character : rotatedText) {
            if (character == '1') {
                transformedText += "\xE2\x96\x88\xE2\x96\x88";
            } else if (character == '0') {
                transformedText += "  ";
            } else {
                transformedText += character;
            }
        }

        rotatedTiles.push_back(transformedText);
    }

    return rotatedTiles;
}





std::vector<std::string> Read::flipTiles(const std::vector<std::string> &texts) {
    std::vector<std::string> flippedTiles;

    for (const std::string &text : texts) {
        std::string flipText;
        std::vector<std::string> lines;
        std::string  line;
 
        for (char character : text) {
            if (character == '\n') {
                lines.push_back(line);
                line.clear();
        } else if (character == '1') {
            line += "\xE2\x96\x88\xE2\x96\x88";
        } else if (character == '0') {
            line += "  ";
        } else {
            line += character;
        }
    }
        for (int i = lines.size() - 1; i >= 0; --i) {
            flipText += lines[i] + '\n';
        }

        flippedTiles.push_back(flipText);
    }

    return flippedTiles;
}


