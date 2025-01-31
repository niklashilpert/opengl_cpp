//
// Created by niklas on 30.01.25.
//

#include <fstream>
#include <string>
#include <sstream>


std::string read_file(const std::string &filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string content;
    try {
        file.open(filename);
        std::stringstream file_stream;
        file_stream << file.rdbuf();
        file.close();
        content = file_stream.str();
    } catch (std::ifstream::failure &_) {
        throw std::runtime_error("Could not read file " + filename);
    }
    return content;
}
