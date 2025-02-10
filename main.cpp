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

    std::vector<float> circles = {};
    std::vector<float> lines = {};

    lines.emplace_back(100.0f);
    lines.emplace_back(100.0f);
    lines.emplace_back(1300.0f);
    lines.emplace_back(100.0f);
    lines.emplace_back(1.0f);
    lines.emplace_back(1.0f);
    lines.emplace_back(1.0f);
    lines.emplace_back(1.0f);
    lines.emplace_back(100.0f);

    circles.emplace_back(100.0f);
    circles.emplace_back(100.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(100.0f);

    circles.emplace_back(1300.0f);
    circles.emplace_back(100.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(1.0f);
    circles.emplace_back(100.0f);


    for (int i = 0; i < 1000; i++) {
        lines.push_back(700 + sinf(2.0f * M_PI * i / 100) * 300);
        lines.push_back(700 + cosf(2.0f * M_PI * i / 100) * 300);
        lines.push_back(700 + sinf(2.0f * M_PI * (i+1) / 100) * 300);
        lines.push_back(700 + cosf(2.0f * M_PI * (i+1) / 100) * 300);
        lines.push_back(1);
        lines.push_back(1);
        lines.push_back(1);
        lines.push_back(1);
        lines.push_back(50);
    }


    for (int i = 0; i < 1000; i++) {
        circles.push_back(700 + sinf(2.0f * M_PI * i / 100) * 300);
        circles.push_back(700 + cosf(2.0f * M_PI * i / 100) * 300);
        circles.push_back(1);
        circles.push_back(1);
        circles.push_back(1);
        circles.push_back(1);
        circles.push_back(50);
    }




    unsigned int circleVBO, circleVAO;
    glGenBuffers(1, &circleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circles.size(), circles.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &circleVAO);
    glBindVertexArray(circleVAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int lineVBO, lineVAO;
    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lines.size(), lines.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(4 * sizeof(float)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(8 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    while (!window.should_close()) {
        const double startTime = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const int width = window.get_width();
        const int height = window.get_height();

        lineShader->setInt("screenWidth", width);
        lineShader->setInt("screenHeight", height);
        circleShader->setInt("screenWidth", width);
        circleShader->setInt("screenHeight", height);

        lineShader->use();
        glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        glBindVertexArray(lineVAO);
        glDrawArrays(GL_POINTS, 0, lines.size());

        circleShader->use();
        glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_POINTS, 0, circles.size());

        const double endTime = glfwGetTime();
        std::cout << round((endTime - startTime) * 1000000) / 1000 << " ms" << std::endl;

        window.updateBuffers();

        Window::updateEvents();
    }

    delete lineShader;
}
