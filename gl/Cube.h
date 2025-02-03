//
// Created by niklas on 02.02.25.
//

#ifndef CUBE_H
#define CUBE_H
#include "Texture.h"

const std::string GRASS_TOP_PATH = "resources/textures/grass/top.png";
const std::string GRASS_SIDE_PATH = "resources/textures/grass/side.png";
const std::string GRASS_BOTTOM_PATH = "resources/textures/grass/bottom.png";

const std::string DEFAULT_CUBE_PATH = "resources/textures/default/default.png";

class Cube {
public:
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    const Texture texture_front;
    const Texture texture_left;
    const Texture texture_right;
    const Texture texture_back;
    const Texture texture_top;
    const Texture texture_bottom;
    Cube(
        const glm::mat4 &view_matrix,
        const glm::mat4 &projection_matrix,
        const std::string &front_resource,
        const std::string &left_resource,
        const std::string &right_resource,
        const std::string &back_resource,
        const std::string &top_resource,
        const std::string &bottom_resource
    );
    void draw() const;
    void set_view_matrix(const glm::mat4 &view) const;
    void set_model_matrix(const glm::mat4 &model) const;
    void set_projection_matrix(const glm::mat4 &projection) const;

};

class GrassBlock : public Cube {
public:
    GrassBlock(const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) : Cube(
        view_matrix,
        projection_matrix,
        GRASS_SIDE_PATH,
        GRASS_SIDE_PATH,
        GRASS_SIDE_PATH,
        GRASS_SIDE_PATH,
        GRASS_TOP_PATH,
        GRASS_BOTTOM_PATH) {}
};

class DefaultCube : public Cube {
public:
    DefaultCube(const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) : Cube(
        view_matrix,
        projection_matrix,
        DEFAULT_CUBE_PATH,
        DEFAULT_CUBE_PATH,
        DEFAULT_CUBE_PATH,
        DEFAULT_CUBE_PATH,
        DEFAULT_CUBE_PATH,
        DEFAULT_CUBE_PATH) {}
};



#endif //CUBE_H
