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

    const auto circleShader = gl::loadCircleShader();

    const auto lineShader = gl::loadLineShader();

    /*constexpr float vertices[] = {
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
    glynableVertexAttribArray(2);*/

    constexpr float vertices[] = {
        200, 200, 1300, 1300, 1, 0, 1, 1, 100,
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(4 * sizeof(float)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(8 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDisable(GL_CULL_FACE);

    while (!window.should_close()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        lineShader->setInt("screenWidth", window.get_width());
        lineShader->setInt("screenHeight", window.get_height());

        //glDrawArrays(GL_POINTS, 0, 5);
        glDrawArrays(GL_POINTS, 0, sizeof(vertices) / 9 / sizeof(float));

        window.updateBuffers();

        Window::updateEvents();
    }

    delete lineShader;
}
