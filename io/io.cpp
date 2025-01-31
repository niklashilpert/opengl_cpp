//
// Created by niklas on 30.01.25.
//

#include <fstream>
#include <iostream>
#include <string>


std::string read_file(const std::string *filename) {
    std::ifstream file(*filename);
    std::string content;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            content.append(line).append("\n");
        }
    }
    return content;
}
