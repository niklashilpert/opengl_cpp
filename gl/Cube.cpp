//
// Created by niklas on 02.02.25.
//

#include "Cube.h"

#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

const std::vector front_vertices {
    Vertex {.5, .5,  .5, 1.0f, 1.0f},
    Vertex {-.5, .5,  .5, 0, 1.0f},
    Vertex {.5, -.5,  .5, 1.0f, 0},
    Vertex {-.5, -.5,  .5, 0, 0},
};

const std::vector left_vertices {
    Vertex {-.5, .5,  .5, 1.0f, 1.0f},
    Vertex {-.5, .5,  -.5, 0, 1.0f},
    Vertex {-.5, -.5,  .5, 1.0f, 0},
    Vertex {-.5, -.5,  -.5, 0, 0}
};

const std::vector top_vertices {
    Vertex {.5, .5,  .5, 1.0f, 1.0f},
    Vertex {.5, .5,  -.5, 0, 1.0f},
    Vertex {-.5, .5,  .5, 1.0f, 0},
    Vertex {-.5, .5,  -.5, 0, 0}
};

const std::vector back_vertices {
    Vertex {.5, .5,  -.5, 0, 1.0f},
    Vertex {-.5, .5,  -.5, 1.0f, 1.0f},
    Vertex {.5, -.5,  -.5, 0, 0},
    Vertex {-.5, -.5,  -.5, 1.0f, 0},
};

const std::vector right_vertices {
    Vertex {.5, .5,  .5, 0, 1.0f},
    Vertex {.5, .5,  -.5, 1.0f, 1.0f},
    Vertex {.5, -.5,  .5, 0, 0},
    Vertex {.5, -.5,  -.5, 1.0f, 0}
};

const std::vector bottom_vertices {
    Vertex {.5, -.5,  .5, 0, 1.0f},
    Vertex {.5, -.5,  -.5, 1.0f, 1.0f},
    Vertex {-.5, -.5,  .5, 0, 0},
    Vertex {-.5, -.5,  -.5, 1.0f, 0}
};

const std::vector<unsigned int> indices = {
    0, 1, 3,
    0, 2, 3,
};

typedef struct TexturePos {
    glm::vec3 position;
    Texture texture;
} TexturePos;

Cube::Cube(
    const glm::mat4 &view_matrix,
    const glm::mat4 &projection_matrix,
    const std::string &front_resource,
    const std::string &left_resource,
    const std::string &right_resource,
    const std::string &back_resource,
    const std::string &top_resource,
    const std::string &bottom_resource
    ) : view_matrix(view_matrix),
        projection_matrix(projection_matrix),
        texture_front(front_resource, front_vertices, indices, GL_RGB),
        texture_left(left_resource, left_vertices, indices, GL_RGB),
        texture_right(right_resource, right_vertices, indices, GL_RGB),
        texture_back(back_resource, back_vertices, indices, GL_RGB),
        texture_top(top_resource, top_vertices, indices, GL_RGB),
        texture_bottom(bottom_resource, bottom_vertices, indices, GL_RGB)
{
    texture_front.set_matrix("projection", projection_matrix);
    texture_back.set_matrix("projection", projection_matrix);
    texture_left.set_matrix("projection", projection_matrix);
    texture_right.set_matrix("projection", projection_matrix);
    texture_top.set_matrix("projection", projection_matrix);
    texture_bottom.set_matrix("projection", projection_matrix);

    texture_front.set_matrix("view", view_matrix);
    texture_back.set_matrix("view", view_matrix);
    texture_left.set_matrix("view", view_matrix);
    texture_right.set_matrix("view", view_matrix);
    texture_top.set_matrix("view", view_matrix);
    texture_bottom.set_matrix("view", view_matrix);
}

void Cube::draw() const {
    texture_front.draw();
    texture_back.draw();
    texture_left.draw();
    texture_right.draw();
    texture_top.draw();
    texture_bottom.draw();
}

void Cube::set_view_matrix(const glm::mat4 &view) const {
    texture_front.set_matrix("view", view);
    texture_back.set_matrix("view", view);
    texture_left.set_matrix("view", view);
    texture_right.set_matrix("view", view);
    texture_top.set_matrix("view", view);
    texture_bottom.set_matrix("view", view);
}


void Cube::set_model_matrix(const glm::mat4 &model) const{
    texture_front.set_matrix("model", model);
    texture_back.set_matrix("model", model);
    texture_left.set_matrix("model", model);
    texture_right.set_matrix("model", model);
    texture_top.set_matrix("model", model);
    texture_bottom.set_matrix("model", model);
}

void Cube::set_projection_matrix(const glm::mat4 &projection) const {
    texture_front.set_matrix("projection", projection);
    texture_back.set_matrix("projection", projection);
    texture_left.set_matrix("projection", projection);
    texture_right.set_matrix("projection", projection);
    texture_top.set_matrix("projection", projection);
    texture_bottom.set_matrix("projection", projection);
}
