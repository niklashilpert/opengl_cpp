//
// Created by niklas on 31.01.25.
//

#include <glad/glad.h>
#include "Shader.h"

#include <iostream>
#include <ostream>

#include "../io/io.h"

std::string get_type_name(const int type) {
    std::string type_name;
    switch (type) {
        case GL_VERTEX_SHADER:
            type_name = "VERTEX";
        break;
        case GL_FRAGMENT_SHADER:
            type_name = "FRAGMENT";
        break;
        case GL_GEOMETRY_SHADER:
            type_name = "GEOMETRY";
        break;
        case GL_COMPUTE_SHADER:
            type_name = "COMPUTE";
        break;
        default:
            type_name = "UNKNOWN";
    }
    return type_name;
}

unsigned int create_shader(const int type, const std::string &source) {
    const unsigned int shader = glCreateShader(type);

    const char *c_source = source.c_str();
    glShaderSource(shader, 1, &c_source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "ERROR::SHADER::" << get_type_name(type) << "::COMPILATION_FAILED" << std::endl;
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        return 0;
    }

    return shader;
}


Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
    const std::string vertex_source = read_file(vertex_path);
    const std::string fragment_source = read_file(fragment_path);
    const unsigned int vertex_id = create_shader(GL_VERTEX_SHADER, vertex_source);
    const unsigned int fragment_id = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    id = glCreateProgram();
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
        char info_log[512];
        glGetProgramInfoLog(id, 512, nullptr, info_log);
        std::cerr << info_log << std::endl;
    }

}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setFloat3(const std::string &name, float value1, float value2, float value3) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
}

void Shader::setBool(const std::string &name, const bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}


