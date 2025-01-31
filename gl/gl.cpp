//
// Created by niklas on 30.01.25.
//

#include "gl.h"
#include "../io/io.h"

#include <iostream>
#include <ostream>
#include <glad/glad.h>

std::string get_type_name(const int type) {
    std::string type_name;
    switch (type) {
        case GL_VERTEX_SHADER:
            type_name = "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            type_name = "fragment";
            break;
        case GL_GEOMETRY_SHADER:
            type_name = "geometry";
            break;
        case GL_COMPUTE_SHADER:
            type_name = "compute";
            break;
        default:
            type_name = "unknown";
    }
    return type_name;
}

unsigned int create_shader(const int type, const std::string *filename) {
    if (filename == nullptr) {
        std::cerr << "Filename is null" << std::endl;
        return 0;
    }

    const std::string source = read_file(filename);
    if (source.empty()) {
        std::cerr << "Failed to read file " << *filename << std::endl;
        return 0;
    }

    const unsigned int shader = glCreateShader(type);

    const char *c_source = source.c_str();
    glShaderSource(shader, 1, &c_source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "Failed to create " << get_type_name(type) << " shader." << std::endl;
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        return 0;
    }

    return shader;
}

unsigned int create_program(const std::vector<unsigned int> &shaders) {
    unsigned int program = glCreateProgram();
    for (unsigned int shader: shaders) {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        std::cerr << "Failed to link program." << std::endl;
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        return 0;
    }

    return program;
}
