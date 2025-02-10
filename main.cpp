#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl/CubeRenderer.h"
#include "window/window.h"
#include "gl/Texture.h"
#include "gl/TextureInstance.h"


const std::string SHADER_DIR = "resources/shaders/";
const std::string TEXTURE_DIR = "resources/textures/";

const std::string VERTEX_SHADER_FILE = SHADER_DIR + "shader.vert";
const std::string FRAGMENT_SHADER_FILE = SHADER_DIR + "shader.frag";



int main() {
    const Window window(800, 800, "OpenGL - Test");

    const auto shader = gl::loadCircleShader();
    shader->use();

    constexpr float vertices[] = {
        0.5f, 0.5f, 0, 1, 1, .1f,
        -0.5f, -0.5f, 1, 0, 1, .3f,
        0.5f, -0.5f, 1, 1, 0, .2f,
        -0.5f, 0.5f, 0, 1, 0, .4f,
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(5 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawArrays(GL_POINTS, 0, 4);
    window.updateBuffers();

    while (!window.should_close()) {
        Window::updateEvents();
    }

    delete shader;
}
