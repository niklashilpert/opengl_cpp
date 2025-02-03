#include <cmath>
#include <iostream>
#include <string>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/window.h"
#include "gl/Cube.h"

#include "gl/Shader.h"
#include "gl/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const std::string SHADER_DIR = "resources/shaders/";
const std::string TEXTURE_DIR = "resources/textures/";

const std::string VERTEX_SHADER_FILE = SHADER_DIR + "shader.vert";
const std::string FRAGMENT_SHADER_FILE = SHADER_DIR + "shader.frag";

void renderCube() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return;
    }

    GLFWwindow *window = create_window(800, 640, "OpenGL - Test");
    if (window == nullptr) {
        return;
    }





    std::string path = "resources/textures/default/default.png";
    //std::string path = "resources/textures/grass/side.png";
    //std::string path2 = "resources/textures/grass/top.png";
    //std::string path3 = "resources/textures/grass/bottom.png";


    const glm::mat4 projection = glm::perspective(glm::radians(30.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

    auto view = glm::mat4(1.0f);
    view = translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
    view = rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = rotate(view, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    DefaultCube cube1(view, projection);
    DefaultCube cube2(view, projection);
    GrassBlock cube3(view, projection);
    GrassBlock cube4(view, projection);
    DefaultCube cube5(view, projection);
    DefaultCube cube6(view, projection);

    auto model1 = glm::mat4(1.0f);
    glm::mat4 model2 = translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));

    auto model3 = glm::mat4(1.0f);
    model3 = translate(model3, glm::vec3(0, 1, -1));
    auto model4 = glm::mat4(1.0f);
    model4 = translate(model4, glm::vec3(1, 1, -1));
    auto model5 = glm::mat4(1.0f);
    model5 = translate(model5, glm::vec3(0, 0, -1));
    auto model6 = glm::mat4(1.0f);
    model6 = translate(model6, glm::vec3(1, 0, -1));


    cube1.set_model_matrix(model1);
    cube2.set_model_matrix(model2);
    cube3.set_model_matrix(model3);
    cube4.set_model_matrix(model4);
    cube5.set_model_matrix(model5);
    cube6.set_model_matrix(model6);

    while (!glfwWindowShouldClose(window)) {
        std::cout << window_width << " " << window_height << std::endl;

        glm::mat4 projection = glm::perspective(glm::radians(30.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);


        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double last_frame_time = glfwGetTime();

        const auto time = static_cast<float>(glfwGetTime());


        view = glm::mat4(1.0f);
        view = translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        view = rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = rotate(view, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = rotate(view, time, glm::vec3(0.0f, 1.0f, 0.0f));


        cube1.set_view_matrix(view);
        cube2.set_view_matrix(view);
        cube3.set_view_matrix(view);
        cube4.set_view_matrix(view);
        cube5.set_view_matrix(view);
        cube6.set_view_matrix(view);


        cube1.set_projection_matrix(projection);
        cube2.set_projection_matrix(projection);
        cube3.set_projection_matrix(projection);
        cube4.set_projection_matrix(projection);
        cube5.set_projection_matrix(projection);
        cube6.set_projection_matrix(projection);



        /*model1 = rotate(model1, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model1 = rotate(model1, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model1 = rotate(model1, time, glm::vec3(1.0f, 1.0f, 0.0f));

        model2 = rotate(model2, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model2 = rotate(model2, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model2 = rotate(model2, time, glm::vec3(1.0f, 1.0f, 0.0f));*/


        cube1.draw();
        cube2.draw();
        cube3.draw();
        cube4.draw();
        cube5.draw();
        cube6.draw();

        glfwSwapBuffers(window);

        double current_frame_time = glfwGetTime();
        std::cout << round((current_frame_time - last_frame_time) * 1000000) / 1000 << "ms" << std::endl;

        glfwPollEvents();
    }

    printf("Terminating...\n");

    glfwDestroyWindow(window);
    glfwTerminate();

}


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

    const Shader shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");

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

int texture_test() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return 1;
    }

    GLFWwindow *window = create_window(640, 640, "OpenGL - Test");
    if (window == nullptr) {
        return 1;
    }

    const std::vector wallVertices = {
        Vertex {1,  1, 0.0f,  1, 0, 0,   1.0f, 1.0f},    // top right
        Vertex {1, -1, 0.0f,   1, 1, 1,   1.0f, 0.0f},    // bottom right
        Vertex {-1,  1, 0.0f,   1, 1, 1,  0.0f, 1.0f},   // top left
        Vertex {-1, -1, 0.0f,   1, 1, 1,   0.0f, 0.0f},   // bottom left
    };

    const std::vector ballVertices = {
        Vertex {0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f},    // top right
        Vertex {0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f},    // bottom right
        Vertex {-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f},   // top left
        Vertex {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f},   // bottom left
    };

    const std::vector<unsigned int> indices = {
        0, 1, 3,
        0, 2, 3,
    };

    const Texture wall("resources/textures/wall.png", wallVertices, indices, GL_RGB);
    const Texture ball("resources/textures/basketball.png", ballVertices, indices, GL_RGBA);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto time = static_cast<float>(glfwGetTime());
        const float x_offset = cosf(time * 3) / 3;
        const float y_offset = sinf(time * 3) / 3;

        auto model = glm::mat4(1.0f);
        model = translate(model, glm::vec3(x_offset, 0, 0.0f));
        model = rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        model = rotate(model, time * 2, glm::vec3(0.0f, 0.0f, 1.0f));

        auto view = glm::mat4(1.0f);
        view = translate(view, glm::vec3(0, 0, -3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(30.0f), 640.f/640.0f, 0.1f, 100.0f);

        ball.set_matrix("model", model);
        ball.set_matrix("view", view);
        ball.set_matrix("projection", projection);
        ball.draw();

        auto model2 = glm::mat4(1.0f);

        auto viewWall = glm::mat4(1.0f);
        viewWall = translate(viewWall, glm::vec3(0.0f, 0.0f, -3.0f));


        wall.set_matrix("projection", projection);
        wall.set_matrix("model", model2);
        wall.set_matrix("view", viewWall);
        wall.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    printf("Terminating...\n");

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


int main() {
    //texture_test();
    renderCube();
}
