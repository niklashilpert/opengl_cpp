#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/window.h"
#include "gl/gl.h"
#include "io/io.h"

const std::string VERTEX_SHADER_FILE = "shaders/shader.vert";
const std::string FRAGMENT_SHADER_FILE = "shaders/shader_orange.frag";

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
        0.0f,  0.0f, 0.0f,  // 0: center
        -1.0f, 1.0f, 0.0f,  // 1: top left
        -1.0f, 0.0f, 0.0f,  // 2: left
        -1.0f, -1.0f, 0.0f, // 3: bottom left
        0.0f, 1.0f, 0.0f,   // 4: top
        0.0f, -1.0f, 0.0f,  // 5: bottom
        1.0f, 1.0f, 0.0f,   // 6: top right
        1.0f, 0.0f, 0.0f,   // 7: right
        1.0f, -1.0f, 0.0f,  // 8: bottom right
    };

    const unsigned int top_left_square[] = {
        1, 4, 0,
        1, 2, 0,
    };

    const unsigned int bottom_right_square[] = {
        0, 7, 8,
        0, 5, 8,
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    unsigned int TOP_LEFT_EBO;
    glGenBuffers(1, &TOP_LEFT_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TOP_LEFT_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(top_left_square), top_left_square, GL_STATIC_DRAW);

    unsigned int BOTTOM_RIGHT;
    glGenBuffers(1, &BOTTOM_RIGHT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BOTTOM_RIGHT);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottom_right_square), bottom_right_square, GL_STATIC_DRAW);

    const std::string vertex_shader_file("shaders/shader.vert");
    const std::string orange_fragment_shader_file("shaders/shader_orange.frag");
    const std::string yellow_fragment_shader_file("shaders/shader_yellow.frag");

    const unsigned int vertex_shader = create_shader(GL_VERTEX_SHADER, &vertex_shader_file);
    const unsigned int orange_fragment_shader = create_shader(GL_FRAGMENT_SHADER, &orange_fragment_shader_file);
    const unsigned int yellow_fragment_shader = create_shader(GL_FRAGMENT_SHADER, &yellow_fragment_shader_file);

    const unsigned int orange_program = create_program({vertex_shader, orange_fragment_shader});
    const unsigned int yellow_program = create_program({vertex_shader, yellow_fragment_shader});

    glDeleteShader(vertex_shader);
    glDeleteShader(orange_fragment_shader);
    glDeleteShader(yellow_fragment_shader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TOP_LEFT_EBO);
        glUseProgram(orange_program);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BOTTOM_RIGHT);
        glUseProgram(yellow_program);
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
