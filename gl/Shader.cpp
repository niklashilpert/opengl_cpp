//
// Created by niklas on 31.01.25.
//

#include <glad/glad.h>
#include "Shader.h"

#include <iostream>
#include <ostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "../io/io.h"

namespace gl {
    std::string getTypeName(const int type) {
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

    int getType(const std::string &path) {
        if (path.ends_with(".vert")) {
            return GL_VERTEX_SHADER;
        }
        if (path.ends_with(".frag")) {
            return GL_FRAGMENT_SHADER;
        }
        if (path.ends_with(".geom")) {
            return GL_GEOMETRY_SHADER;
        }
        if (path.ends_with(".comp")) {
            return GL_COMPUTE_SHADER;
        }
        throw std::runtime_error("Unknown shader type: " + path);
    }

    unsigned int createShader(const int type, const std::string &source) {
        const unsigned int shader = glCreateShader(type);

        const char *c_source = source.c_str();
        glShaderSource(shader, 1, &c_source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            std::cerr << "ERROR::SHADER::" << getTypeName(type) << "::COMPILATION_FAILED" << std::endl;
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << infoLog << std::endl;
            return 0;
        }

        return shader;
    }


    Shader::Shader(const std::vector<std::string> &paths) {
        id = glCreateProgram();

        for (const auto &path: paths) {
            const std::string source = readFile(path);
            const unsigned int shader_id = createShader(getType(path), source);
            glAttachShader(id, shader_id);
            glDeleteShader(shader_id);
        }
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

    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::use() const {
        glUseProgram(id);
    }

    void Shader::setFloat3(const std::string &name, const float value1, const float value2, const float value3) const {
        use();
        glUniform3f(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
    }

    void Shader::setBool(const std::string &name, const bool value) const {
        use();
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
    }

    void Shader::setInt(const std::string &name, const int value) const {
        use();
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, const float value) const {
        use();
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
        use();
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
    }


    Shader *loadTextureShader() {
        return new Shader({TEXTURE_VERTEX_SHADER_FILE, TEXTURE_FRAGMENT_SHADER_FILE});
    }

    Shader *loadCircleShader() {
        return new Shader(
        {
            CIRCLE_VERTEX_SHADER_FILE,
            CIRCLE_GEOMETRY_SHADER_FILE,
            CIRCLE_FRAGMENT_SHADER_FILE
            }
        );
    }
    Shader *loadLineShader() {
        return new Shader(
       {
           LINE_VERTEX_SHADER_FILE,
           LINE_GEOMETRY_SHADER_FILE,
           LINE_FRAGMENT_SHADER_FILE
           }
       );
    }
}
