#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window/window.h"
#include "gl/Texture.h"
#include "gl/Cube.h"



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


    constexpr auto model1 = glm::mat4(1.0f);
    const glm::mat4 model2 = translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));
    const glm::mat4 model3 = translate(glm::mat4(1.0f), glm::vec3(0, 1, -1));
    const glm::mat4 model4 = translate(glm::mat4(1.0f), glm::vec3(1, 1, -1));
    const glm::mat4 model5 = translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
    const glm::mat4 model6 = translate(glm::mat4(1.0f), glm::vec3(1, 0, -1));

    const Cube cube1 = make_grass(model1);
    const Cube cube2 = make_grass(model2);
    const Cube cube3 = make_grass(model3);
    const Cube cube4 = make_grass(model4);
    const Cube cube5 = make_brick(model5);
    const Cube cube6 = make_brick(model6);

    while (!glfwWindowShouldClose(window)) {
        const double last_frame_time = glfwGetTime();

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto time = static_cast<float>(glfwGetTime());

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
        Texture::shader->setMat4("projection", projection);

        auto view = glm::mat4(1.0f);
        view = translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        view = rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = rotate(view, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = rotate(view, time, glm::vec3(0, 1, 0));
        Texture::shader->setMat4("view", view);


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

int main() {
    //texture_test();
    renderCube();
}
