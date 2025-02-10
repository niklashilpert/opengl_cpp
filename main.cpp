#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>
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

struct Circle {
glm::vec2 position;
float radius;
glm::vec3 color;
};

int main() {
    const Window window(800, 800, "OpenGL - Test");

    const auto shader = gl::loadCircleShader();
    shader->use();

    constexpr float vertices[] = {
        0, 0, 1, 0, 1, 100,
        0.5f, 0.5f, 0, 1, 1, 300,
        -0.5f, -0.5f, 1, 0, 1, 80,
        0.5f, -0.5f, 1, 1, 0, 60,
        -0.5f, 0.5f, 0, 1, 0, 40,
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


    while (!window.should_close()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->setInt("screenWidth", window.get_width());
        shader->setInt("screenHeight", window.get_height());

        glDrawArrays(GL_POINTS, 0, 5);
        window.updateBuffers();

        Window::updateEvents();
    }

    delete shader;
}
