#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/window.h"
#include "gl/Shader.h"

const std::string VERTEX_SHADER_FILE = "shaders/shader.vert";
const std::string FRAGMENT_SHADER_FILE = "shaders/shader.frag";

int test1() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return 1;
    }

    GLFWwindow *window = create_window(640, 640, "OpenGL - Test");
    if (window == nullptr) {
        return 1;
    }

    constexpr float vertices[] = {
        -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // tl - green
        0.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // t  - blue
        -1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // l  - blue
        0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // c  - red

        0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // c  - red
         0.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // b  - blue
         1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // r  - blue
        1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // br - green


    };

    const unsigned int top_left_square[] = {
        0, 1, 3,
        0, 2, 3,
    };

    const unsigned int bottom_right_square[] = {
        4, 5, 7,
        4, 6, 7,
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int TOP_LEFT_EBO;
    glGenBuffers(1, &TOP_LEFT_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TOP_LEFT_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(top_left_square), top_left_square, GL_STATIC_DRAW);

    unsigned int BOTTOM_RIGHT_EBO;
    glGenBuffers(1, &BOTTOM_RIGHT_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BOTTOM_RIGHT_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottom_right_square), bottom_right_square, GL_STATIC_DRAW);

    const Shader shader("shaders/shader.vert", "shaders/shader.frag");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        const auto time = static_cast<float>(glfwGetTime());
        const float value = std::sinf(time * 5.0f) * .5f;
        const float red(std::sinf(time + .5f) / 2.0f + 0.5f);
        const float green(std::sinf(time +1.0f) / 2.0f + 0.5f);
        const float blue(std::sinf(time) / 2.0f + 0.5f);

        shader.setFloat3("offset", value, 0, 0);
        shader.setFloat3("color", red, green, blue);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TOP_LEFT_EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BOTTOM_RIGHT_EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    printf("Terminating...\n");

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


int main() {
    test1();
}
