#include "../include/read.hpp"
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


