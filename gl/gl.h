//
// Created by niklas on 30.01.25.
//

#ifndef SHADERS_H
#define SHADERS_H
#include <string>
#include <vector>

unsigned int create_shader(int type, const std::string *filename);
unsigned int create_program(const std::vector<unsigned int> &shaders);

#endif //SHADERS_H
